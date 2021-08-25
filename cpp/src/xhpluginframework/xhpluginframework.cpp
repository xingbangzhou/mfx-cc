#include "stable.h"
#include "xhpluginframework/xhpluginframework.h"
#include "xhpluginframework_p.h"

XhPluginFramework::XhPluginFramework()
    : XhPlugin()
{
    qRegisterMetaType<QSharedPointer<XhPlugin> >("QSharedPointer<XhPlugin>");
}

bool XhPluginFramework::init()
{
    Q_D(XhPluginFramework);

    XhPluginPrivate::Locker sync(&d->lock);
    d->waitOnOperation(&d->lock, "Framework.init", true);
    switch (d->state)
    {
    case XhPlugin::INSTALLED:
    case XhPlugin::RESOLVED:
        break;
    case XhPlugin::STARTING:
    case XhPlugin::ACTIVE:
        return false;
    }
    d->init();
    return true;
}

void XhPluginFramework::start()
{
    Q_D(XhPluginFramework);

    {
        XhPluginPrivate::Locker sync(&d->lock);
        d->waitOnOperation(&d->lock, "XhPluginFramework::start", true);

        switch (d->state)
        {
        case INSTALLED:
        case RESOLVED:
            d->init();
        case STARTING:
            d->operation.fetchAndStoreOrdered(XhPluginPrivate::ACTIVATING);
            break;
        case ACTIVE:
            return;
        default:
            return;
        }
    }

    d->activate(d->pluginContext.data());

    {
        XhPluginPrivate::Locker sync(&d->lock);
        d->state = ACTIVE;
        d->operation = XhPluginPrivate::IDLE;
        d->lock.wakeAll();
        // d->fwCtx->listeners.emitFrameworkEvent(
        //     ctkPluginFrameworkEvent(ctkPluginFrameworkEvent::FRAMEWORK_STARTED, this->d_func()->q_func()));
    }
}

void XhPluginFramework::stop()
{
    Q_D(XhPluginFramework);
    d->shutdown();
}

void XhPluginFramework::uninstall()
{

}
