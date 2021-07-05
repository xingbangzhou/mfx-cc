#include "leplugin_p.h"
#include "lepluginframework/leplugincontext.h"
#include "lepluginframework/lepluginactivator.h"
#include "leplugincontext_p.h"
#include "lepluginframeworkcontext.h"
#include "lepluginframework/leserviceregistration.h"
#include "leservices.h"
#include "leservicereference_p.h"

#include <QDateTime>
#include <iostream>

qint64 msecsTo(const QDateTime& t1, const QDateTime& t2)
{
    QDateTime utcT1 = t1.toUTC();
    QDateTime utcT2 = t2.toUTC();

    return static_cast<qint64>(utcT1.daysTo(utcT2)) * static_cast<qint64>(1000*3600*24)
      + static_cast<qint64>(utcT1.time().msecsTo(utcT2.time()));
}

const LePlugin::States LePluginPrivate::RESOLVED_FLAGS = LePlugin::RESOLVED | LePlugin::STARTING | LePlugin::ACTIVE | LePlugin::STOPPING;

//----------------------------------------------------------------------------
void LePluginPrivate::LockObject::lock()
{
  m_lock.lock();
}

bool LePluginPrivate::LockObject::tryLock()
{
  return m_lock.tryLock();
}

bool LePluginPrivate::LockObject::tryLock(int timeout)
{
  return m_lock.tryLock(timeout);
}

void LePluginPrivate::LockObject::unlock()
{
  m_lock.unlock();
}

bool LePluginPrivate::LockObject::wait(unsigned long time)
{
  return m_condition.wait(&m_lock, time);
}

void LePluginPrivate::LockObject::wakeAll()
{
  m_condition.wakeAll();
}

void LePluginPrivate::LockObject::wakeOne()
{
  m_condition.wakeOne();
}

//----------------------------------------------------------------------------
LePluginPrivate::LePluginPrivate(QWeakPointer<LePlugin> qq,
                                 LePluginFrameworkContext* fw,
                                 const QString& loc)
    : q_ptr(qq), fwCtx(fw), location(loc),
      state(LePlugin::INSTALLED), pluginContext(nullptr), pluginActivator(nullptr), pluginLoader(loc)
    , logger("LePlugin")
{

}

LePluginPrivate::~LePluginPrivate()
{

}


LePlugin::State LePluginPrivate::getUpdatedState()
{
    if (state == LePlugin::INSTALLED)
    {
        Locker sync(&operationLock);
        getUpdatedState_unlocked();
    }
    return state;
}

LePlugin::State LePluginPrivate::getUpdatedState_unlocked()
{
	if (state == LePlugin::INSTALLED)
	{
		operation.fetchAndStoreOrdered(RESOLVING);
		fwCtx->resolvePlugin(this);
		state = LePlugin::RESOLVED;
		
		fwCtx->logger().info("update state: RESOLVED");

		operation.fetchAndStoreOrdered(IDLE);
	}
    return state;
}

void LePluginPrivate::finalizeActivation()
{
    Locker sync(&operationLock);

    switch (getUpdatedState_unlocked())
    {
    case LePlugin::INSTALLED:
        return;
    case LePlugin::STARTING:
        if (operation.fetchAndAddOrdered(0) == ACTIVATING) return;
    case LePlugin::RESOLVED:
    {
        state = LePlugin::STARTING;
        operation.fetchAndStoreOrdered(ACTIVATING);
        if (!pluginContext)
        {
            pluginContext.reset(new LePluginContext(this));
        }
        startDependencies();
        start0();
        operation.fetchAndStoreOrdered(IDLE);
        operationLock.wakeAll();
        break;
    }
    }
}

void LePluginPrivate::start0()
{
    QString error = QString::null;

	if (!pluginLoader.load())
	{
		error = QString("Loading plugin %1 failed: %2").arg(pluginLoader.fileName()).arg(pluginLoader.errorString());
	}
	else 
	{
		pluginActivator = qobject_cast<LePluginActivator*>(pluginLoader.instance());
		if (!pluginActivator)
		{
			error = QString("PluginActivator is NULL");
		}
		else
		{
			pluginActivator->start(pluginContext.data());			
			state = LePlugin::ACTIVE;
		}
	}

	if (error.isEmpty())
	{
		fwCtx->logger().info("Plugin start0: Success");
	}
	else 
	{
		fwCtx->logger().error(error);
	}
}

void LePluginPrivate::stop0()
{
    bool wasStarted = state == LePlugin::ACTIVE;
    state = LePlugin::STOPPING;
    operation.fetchAndStoreOrdered(DEACTIVATING);

    // fwCtx->listeners.emitPluginChanged(ctkPluginEvent(ctkPluginEvent::STOPPING, q_func()));

    if (wasStarted && pluginActivator)
    {
        pluginActivator->stop(pluginContext.data());
        if (state != LePlugin::STOPPING)
        {
            return;
        }
        pluginActivator = nullptr;
    }
     if (operation.fetchAndAddOrdered(0) == DEACTIVATING)
     {
         if (pluginContext)
         {
            removePluginResources();
            pluginContext->d_func()->invalidate();
            pluginContext.reset();
         }
     }
     if (state != LePlugin::UNINSTALLED)
     {
        state = LePlugin::RESOLVED;
        // fwCtx->listeners.emitPluginChanged(ctkPluginEvent(ctkPluginEvent::STOPPED, this->q_func()));

        operationLock.wakeAll();
        operation.fetchAndStoreOrdered(IDLE);
     }
}

void LePluginPrivate::waitOnOperation(LockObject* lock, const QString& src, bool longWait)
{
    src;
    if (operation.fetchAndAddOrdered(0) != IDLE)
    {
        quint64 left = longWait ? 20000 : 500;
        QDateTime waitUntil = QDateTime::currentDateTime().addMSecs(left);
        do
        {
            lock->wait(left);
            if (operation.fetchAndOrOrdered(0) == IDLE)
            {
                return;
            }
            left = msecsTo(QDateTime::currentDateTime(), waitUntil);
        } while (left > 0);
    }
}

void LePluginPrivate::startDependencies()
{

}

void LePluginPrivate::removePluginResources()
{
    QList<LeServiceRegistration> srs = fwCtx->services->getRegisteredByPlugin(this);
    QMutableListIterator<LeServiceRegistration> i(srs);
    while (i.hasNext())
    {
        i.next().unregister();
    }

    QList<LeServiceRegistration> s = fwCtx->services->getUsedByPlugin(q_func());
    QListIterator<LeServiceRegistration> i2(s);
    while (i2.hasNext())
    {
        i2.next().getReference().d_func()->ungetService(q_func(), false);
    }
}
