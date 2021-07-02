#include "leplugin_p.h"
#include "lepluginframework/leplugincontext.h"
#include "lepluginframework/lepluginactivator.h"
#include "leplugincontext_p.h"
#include "lepluginframeworkcontext.h"

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
      state(LePlugin::INSTALLED), pluginContext(NULL), pluginActivator(NULL), pluginLoader(loc)
    , logger("LePlugin")
{

}

LePluginPrivate::~LePluginPrivate()
{

}


LePlugin::State LePluginPrivate::getUpdatedState()
{
    if (state & LePlugin::INSTALLED)
    {
        Locker sync(&operationLock);
        getUpdatedState_unlocked();
    }
    return state;
}

LePlugin::State LePluginPrivate::getUpdatedState_unlocked()
{
    if (state & LePlugin::INSTALLED)
    {
        if (state == LePlugin::INSTALLED)
        {
            operation.fetchAndStoreOrdered(RESOLVING);
            fwCtx->resolvePlugin(this);
            state = LePlugin::RESOLVED;
            // fwCtx->listeners.emitPluginChanged(ctkPluginEvent(ctkPluginEvent::RESOLVED, this->q_func()));
            operation.fetchAndStoreOrdered(IDLE);
        }
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

    // fwCtx->listeners.emitPluginChanged(LePluginEvent(LePluginEvent::STARTING, this->q_func()));

    try
    {
        if (!pluginLoader.load())
        {
            error = QString("Loading plugin %1 failed: %2").arg(pluginLoader.fileName()).arg(pluginLoader.errorString());
            throw std::exception();
        }

        pluginActivator = qobject_cast<LePluginActivator*>(pluginLoader.instance());
        if(!pluginActivator)
        {
            throw std::exception();
        }

        pluginActivator->start(pluginContext.data());

        if (state != LePlugin::STARTING)
        {
            if (LePlugin::UNINSTALLED == state)
            {
                error = "ctkPlugin uninstalled during start()";
                throw std::exception();
            }
            else
            {
                error = "ctkPlugin changed state because of refresh during start()";
                throw std::exception();
            }
        }
        state = LePlugin::ACTIVE;
    }
    catch (...)
    {
        
    }

    if (error.isEmpty())
    {
        // fwCtx->listeners.emitPluginChanged(ctkPluginEvent(ctkPluginEvent::STARTED, this->q_func()));
    }
    else if (operation.fetchAndAddOrdered(0) == ACTIVATING)
    {
        state = LePlugin::STOPPING;
        // fwCtx->listeners.emitPluginChanged(ctkPluginEvent(ctkPluginEvent::STOPPING, this->q_func()));

    }

    std::cout << error.toStdString();
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
        pluginActivator = NULL;
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

}
