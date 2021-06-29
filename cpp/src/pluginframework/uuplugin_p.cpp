#include "uuplugin_p.h"
#include "pluginframework/uuplugincontext.h"

#include <QDateTime>

qint64 msecsTo(const QDateTime& t1, const QDateTime& t2)
{
    QDateTime utcT1 = t1.toUTC();
    QDateTime utcT2 = t2.toUTC();

    return static_cast<qint64>(utcT1.daysTo(utcT2)) * static_cast<qint64>(1000*3600*24)
      + static_cast<qint64>(utcT1.time().msecsTo(utcT2.time()));
}

const uuPlugin::States uuPluginPrivate::RESOLVED_FLAGS = uuPlugin::RESOLVED | uuPlugin::STARTING | uuPlugin::ACTIVE | uuPlugin::STOPPING;

//----------------------------------------------------------------------------
void uuPluginPrivate::LockObject::lock()
{
  m_lock.lock();
}

bool uuPluginPrivate::LockObject::tryLock()
{
  return m_lock.tryLock();
}

bool uuPluginPrivate::LockObject::tryLock(int timeout)
{
  return m_lock.tryLock(timeout);
}

void uuPluginPrivate::LockObject::unlock()
{
  m_lock.unlock();
}

bool uuPluginPrivate::LockObject::wait(unsigned long time)
{
  return m_condition.wait(&m_lock, time);
}

void uuPluginPrivate::LockObject::wakeAll()
{
  m_condition.wakeAll();
}

void uuPluginPrivate::LockObject::wakeOne()
{
  m_condition.wakeOne();
}

//----------------------------------------------------------------------------
uuPluginPrivate::uuPluginPrivate(QWeakPointer<uuPlugin> qq,
                                 uuPluginFrameworkContext* fw,
                                 const QString& loc)
    : q_ptr(qq), fwCtx(fw), location(loc),
      state(uuPlugin::INSTALLED), pluginContext(NULL), pluginActivator(NULL),
      pluginLoader(loc)
{

}

uuPluginPrivate::~uuPluginPrivate()
{

}


uuPlugin::State uuPluginPrivate::getUpdatedState()
{
    if (state & uuPlugin::INSTALLED)
    {
        Locker sync(&operationLock);
        getUpdatedState_unlocked();
    }
    return state;
}

uuPlugin::State uuPluginPrivate::getUpdatedState_unlocked()
{
    if (state & uuPlugin::INSTALLED)
    {
        if (state == uuPlugin::INSTALLED)
        {
            operation.fetchAndStoreOrdered(RESOLVING);
            // fwCtx->resolvePlugin(this);
            state = uuPlugin::RESOLVED;
            // fwCtx->listeners.emitPluginChanged(ctkPluginEvent(ctkPluginEvent::RESOLVED, this->q_func()));
            operation.fetchAndStoreOrdered(IDLE);
        }
    }
    return state;
}

void uuPluginPrivate::finalizeActivation()
{
    Locker sync(&operationLock);

    switch (getUpdatedState_unlocked())
    {
    case uuPlugin::INSTALLED:
        return;
    case uuPlugin::STARTING:
        if (operation.fetchAndAddOrdered(0) == ACTIVATING) return;
    case uuPlugin::RESOLVED:
    {
        state = uuPlugin::STARTING;
        operation.fetchAndStoreOrdered(ACTIVATING);
        if (!pluginContext)
        {
            pluginContext.reset(new uuPluginContext(this));
        }
        startDependencies();
        start0();
        operation.fetchAndStoreOrdered(IDLE);
        operationLock.wakeAll();
        break;
    }
    case uuPlugin::ACTIVE:
        break;
    case uuPlugin::STOPPING:
        return;
    case uuPlugin::UNINSTALLED:
        return;

    }
}

void uuPluginPrivate::stop0()
{

}

void uuPluginPrivate::waitOnOperation(LockObject* lock, const QString& src, bool longWait)
{
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
