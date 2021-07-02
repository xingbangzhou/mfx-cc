#include "stable.h"
#include "lepluginframework/lepluginframework.h"
#include "lepluginframework_p.h"

LePluginFramework::LePluginFramework()
    : LePlugin()
{
    qRegisterMetaType<QSharedPointer<LePlugin> >("QSharedPointer<LePlugin>");
}

bool LePluginFramework::init()
{
    Q_D(LePluginFramework);

    LePluginPrivate::Locker sync(&d->lock);
    d->waitOnOperation(&d->lock, "Framework.init", true);
    switch (d->state)
    {
    case LePlugin::INSTALLED:
    case LePlugin::RESOLVED:
        break;
    case LePlugin::STARTING:
    case LePlugin::ACTIVE:
        return false;
    }
    d->init();
    return true;
}

void LePluginFramework::start()
{
    Q_D(LePluginFramework);

    {
        LePluginPrivate::Locker sync(&d->lock);
        d->waitOnOperation(&d->lock, "LePluginFramework::start", true);

        switch (d->state)
        {
        case INSTALLED:
        case RESOLVED:
            d->init();
        case STARTING:
            d->operation.fetchAndStoreOrdered(LePluginPrivate::ACTIVATING);
            break;
        case ACTIVE:
            return;
        default:
            return;
        }
    }

    d->activate(d->pluginContext.data());

    {
        LePluginPrivate::Locker sync(&d->lock);
        d->state = ACTIVE;
        d->operation = LePluginPrivate::IDLE;
        d->lock.wakeAll();
        // d->fwCtx->listeners.emitFrameworkEvent(
        //     ctkPluginFrameworkEvent(ctkPluginFrameworkEvent::FRAMEWORK_STARTED, this->d_func()->q_func()));
    }
}

void LePluginFramework::stop()
{
    Q_D(LePluginFramework);
    d->shutdown();
}

void LePluginFramework::uninstall()
{

}
