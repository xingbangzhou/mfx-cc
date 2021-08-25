#include "xhplugin_p.h"
#include "xhpluginframework/xhplugincontext.h"
#include "xhpluginframework/xhpluginactivator.h"
#include "xhplugincontext_p.h"
#include "xhpluginframeworkcontext.h"
#include "xhpluginframework/xhserviceregistration.h"
#include "xhservices.h"
#include "xhservicereference_p.h"

#include <QDateTime>

qint64 msecsTo(const QDateTime& t1, const QDateTime& t2)
{
    QDateTime utcT1 = t1.toUTC();
    QDateTime utcT2 = t2.toUTC();

    return static_cast<qint64>(utcT1.daysTo(utcT2)) * static_cast<qint64>(1000*3600*24)
      + static_cast<qint64>(utcT1.time().msecsTo(utcT2.time()));
}

const XhPlugin::States XhPluginPrivate::RESOLVED_FLAGS = XhPlugin::RESOLVED | XhPlugin::STARTING | XhPlugin::ACTIVE | XhPlugin::STOPPING;

//----------------------------------------------------------------------------
void XhPluginPrivate::LockObject::lock()
{
	m_lock.lock();
}

bool XhPluginPrivate::LockObject::tryLock()
{
	return m_lock.tryLock();
}

bool XhPluginPrivate::LockObject::tryLock(int timeout)
{
	return m_lock.tryLock(timeout);
}

void XhPluginPrivate::LockObject::unlock()
{
	m_lock.unlock();
}

bool XhPluginPrivate::LockObject::wait(unsigned long time)
{
  return m_condition.wait(&m_lock, time);
}

void XhPluginPrivate::LockObject::wakeAll()
{
  m_condition.wakeAll();
}

void XhPluginPrivate::LockObject::wakeOne()
{
  m_condition.wakeOne();
}

//----------------------------------------------------------------------------
XhPluginPrivate::XhPluginPrivate(QWeakPointer<XhPlugin> qq,
                                 XhPluginFrameworkContext* fw,
                                 const QString& loc)
    : q_ptr(qq), fwCtx(fw), location(loc),
      state(XhPlugin::INSTALLED), pluginContext(nullptr), pluginActivator(nullptr), pluginLoader(loc)
    , logger("XhPlugin")
{

}

XhPluginPrivate::~XhPluginPrivate()
{

}


XhPlugin::State XhPluginPrivate::getUpdatedState()
{
    if (state == XhPlugin::INSTALLED)
    {
        Locker sync(&operationLock);
        getUpdatedState_unlocked();
    }
    return state;
}

XhPlugin::State XhPluginPrivate::getUpdatedState_unlocked()
{
	if (state == XhPlugin::INSTALLED)
	{
		operation.fetchAndStoreOrdered(RESOLVING);
		fwCtx->resolvePlugin(this);
		state = XhPlugin::RESOLVED;
		
		fwCtx->logger().info("update state: RESOLVED");

		operation.fetchAndStoreOrdered(IDLE);
	}
    return state;
}

void XhPluginPrivate::finalizeActivation()
{
    Locker sync(&operationLock);

    switch (getUpdatedState_unlocked())
    {
    case XhPlugin::INSTALLED:
        return;
    case XhPlugin::STARTING:
        if (operation.fetchAndAddOrdered(0) == ACTIVATING) return;
    case XhPlugin::RESOLVED:
    {
        state = XhPlugin::STARTING;
        operation.fetchAndStoreOrdered(ACTIVATING);
        if (!pluginContext)
        {
            pluginContext.reset(new XhPluginContext(this));
        }
        startDependencies();
        start0();
        operation.fetchAndStoreOrdered(IDLE);
        operationLock.wakeAll();
        break;
    }
    }
}

void XhPluginPrivate::start0()
{
    QString error = QString::null;

	if (!pluginLoader.load())
	{
		error = QString("Loading plugin %1 failed: %2").arg(pluginLoader.fileName()).arg(pluginLoader.errorString());
	}
	else 
	{
		pluginActivator = qobject_cast<XhPluginActivator*>(pluginLoader.instance());
		if (!pluginActivator)
		{
			error = QString("PluginActivator is NULL");
		}
		else
		{
			pluginActivator->start(pluginContext.data());			
			state = XhPlugin::ACTIVE;
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

void XhPluginPrivate::stop0()
{
    bool wasStarted = state == XhPlugin::ACTIVE;
    state = XhPlugin::STOPPING;
    operation.fetchAndStoreOrdered(DEACTIVATING);

    // fwCtx->listeners.emitPluginChanged(ctkPluginEvent(ctkPluginEvent::STOPPING, q_func()));

    if (wasStarted && pluginActivator)
    {
        pluginActivator->stop(pluginContext.data());
        if (state != XhPlugin::STOPPING)
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
     if (state != XhPlugin::UNINSTALLED)
     {
        state = XhPlugin::RESOLVED;
        // fwCtx->listeners.emitPluginChanged(ctkPluginEvent(ctkPluginEvent::STOPPED, this->q_func()));

        operationLock.wakeAll();
        operation.fetchAndStoreOrdered(IDLE);
     }
}

void XhPluginPrivate::waitOnOperation(LockObject* lock, const QString& src, bool longWait)
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

void XhPluginPrivate::startDependencies()
{

}

void XhPluginPrivate::removePluginResources()
{
    QList<XhServiceRegistration> srs = fwCtx->services->getRegisteredByPlugin(this);
    QMutableListIterator<XhServiceRegistration> i(srs);
    while (i.hasNext())
    {
        i.next().unregister();
    }

    QList<XhServiceRegistration> s = fwCtx->services->getUsedByPlugin(q_func());
    QListIterator<XhServiceRegistration> i2(s);
    while (i2.hasNext())
    {
        i2.next().getReference().d_func()->ungetService(q_func(), false);
    }
}
