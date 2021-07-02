#ifndef LEPLUGIN_P_H
#define LEPLUGIN_P_H
#include <QWeakPointer>
#include <QMutex>
#include <QWaitCondition>
#include <QPluginLoader>

#include "lepluginframework/leplugin.h"

class LePluginActivator;
class LePluginFrameworkContext;

class LePluginPrivate
{
protected:
    const QWeakPointer<LePlugin> q_ptr;

    class LockObject
    {
    public:
        LockObject() {};

        void lock();
        bool tryLock();
        bool tryLock(int timeout);
        void unlock();

        bool wait(unsigned long time = ULONG_MAX);
        void wakeAll();
        void wakeOne();

    private:
        Q_DISABLE_COPY(LockObject)

        QMutex m_lock;
        QWaitCondition m_condition;
    };

public:
    inline QWeakPointer<LePlugin> q_func() { return q_ptr; }
    inline QWeakPointer<const LePlugin> q_func() const { return q_ptr; }
    friend class LePlugin;

    struct Locker
    {
    Locker(LockObject* obj) : m_Obj(obj) { m_Obj->lock(); }
    ~Locker() { m_Obj->unlock(); }
    private:
      LockObject* m_Obj;
    };

    explicit LePluginPrivate(QWeakPointer<LePlugin> qq,
                             LePluginFrameworkContext* fw,
                             const QString& loc
                             );
    virtual ~LePluginPrivate();

    LePlugin::State getUpdatedState();

    void finalizeActivation();

    void start0();

    void stop0();

    void waitOnOperation(LockObject* lock, const QString& src, bool longWait);

    static const LePlugin::States RESOLVED_FLAGS;

    LeLogger logger;

    LePluginFrameworkContext * const fwCtx;

    const QString location;

    LePlugin::State state;

    QScopedPointer<LePluginContext> pluginContext;

    LePluginActivator* pluginActivator;

    QPluginLoader pluginLoader;

    QAtomicInt operation;
    static const int IDLE = 0;
    static const int ACTIVATING = 1;
    static const int DEACTIVATING = 2;
    static const int RESOLVING = 3;
    static const int UNINSTALLING = 4;
    static const int UNRESOLVING = 5;
    static const int UPDATING = 6;

    LockObject operationLock;

private:

    void startDependencies();

    // Remove a plugins registered listeners, registered services and
    // used services.
    void removePluginResources();

    LePlugin::State getUpdatedState_unlocked();

};

#endif // LEPLUGIN_P_H
