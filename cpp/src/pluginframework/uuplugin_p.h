#ifndef UUPLUGIN_P_H
#define UUPLUGIN_P_H
#include <QWeakPointer>
#include <QMutex>
#include <QWaitCondition>
#include <QPluginLoader>

#include "pluginframework/uuplugin.h"

class uuPluginActivator;
class uuPluginFrameworkContext;

class uuPluginPrivate
{
protected:
    const QWeakPointer<uuPlugin> q_ptr;

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
    inline QWeakPointer<uuPlugin> q_func() { return q_ptr; }
    inline QWeakPointer<const uuPlugin> q_func() const { return q_ptr; }
    friend class uuPlugin;

    struct Locker
    {
    Locker(LockObject* obj) : m_Obj(obj) { m_Obj->lock(); }
    ~Locker() { m_Obj->unlock(); }
    private:
      LockObject* m_Obj;
    };

    explicit uuPluginPrivate(QWeakPointer<uuPlugin> qq,
                             uuPluginFrameworkContext* fw,
                             const QString& loc
                             );
    virtual ~uuPluginPrivate();

    uuPlugin::State getUpdatedState();

    void finalizeActivation();

    void start0();

    void stop0();

    void waitOnOperation(LockObject* lock, const QString& src, bool longWait);

    static const uuPlugin::States RESOLVED_FLAGS;

    uuPluginFrameworkContext * const fwCtx;

    const QString location;

    uuPlugin::State state;

    QScopedPointer<uuPluginContext> pluginContext;

    uuPluginActivator* pluginActivator;

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

    uuPlugin::State getUpdatedState_unlocked();

};

#endif // UUPLUGIN_P_H
