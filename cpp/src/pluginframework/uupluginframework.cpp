#include "stable.h"
#include "pluginframework/uupluginframework.h"
#include "uupluginframework_p.h"

uuPluginFramework::uuPluginFramework()
    : uuPlugin()
{
    qRegisterMetaType<QSharedPointer<uuPlugin> >("QSharedPointer<uuPlugin>");
}

void uuPluginFramework::init()
{
    Q_D(uuPluginFramework);

    uuPluginPrivate::Locker sync(&d->lock);
    d->waitOnOperation(&d->lock, "Framework.init", true);
    switch (d->state)
    {
    case uuPlugin::INSTALLED:
    case uuPlugin::RESOLVED:
        break;
    case uuPlugin::STARTING:
    case uuPlugin::ACTIVE:
        return;
    }
    d->init();
}

void uuPluginFramework::start()
{
    Q_D(uuPluginFramework);

    uuPluginPrivate::Locker sync(&d->lock);
    d->waitOnOperation(&d->lock, "uuPluginFramework::start", true);

    switch (d->state)
    {
    case INSTALLED:
    case RESOLVED:
        d->init();
    case STARTING:
        d->operation.fetchAndStoreOrdered(uuPluginPrivate::ACTIVATING);
    case ACTIVE:
        return;
    }

    d->activate(d->pluginContext.data());

    {
        uuPluginPrivate::Locker sync(&d->lock);
        d->state = ACTIVE;
        d->operation = uuPluginPrivate::IDLE;
        d->lock.wakeAll();
        // d->fwCtx->listeners.emitFrameworkEvent(
        //     ctkPluginFrameworkEvent(ctkPluginFrameworkEvent::FRAMEWORK_STARTED, this->d_func()->q_func()));
    }
}

void uuPluginFramework::stop()
{
    Q_D(uuPluginFramework);
    d->shutdown();
}
