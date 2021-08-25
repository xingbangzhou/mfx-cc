#include "stable.h"
#include "xhpluginframework_p.h"
#include "xhpluginframework/xhplugin_constants.h"
#include "xhpluginframeworkcontext.h"
#include "xhpluginframework/xhplugincontext.h"
#include "xhplugincontext_p.h"

XhPluginFrameworkPrivate::XhPluginFrameworkPrivate(QWeakPointer<XhPlugin> qq, XhPluginFrameworkContext* fw)
    : XhPluginPrivate(qq, fw, XhPluginConstants::SYSTEM_PLUGIN_LOCATION)
{

}

void XhPluginFrameworkPrivate::init()
{
    this->state = XhPlugin::STARTING;
    this->fwCtx->init();
}

void XhPluginFrameworkPrivate::initSystemPlugin()
{
    this->pluginContext.reset(new XhPluginContext(this));
}

void XhPluginFrameworkPrivate::uninitSystemPlugin()
{
    this->pluginContext->d_func()->invalidate();
}

void XhPluginFrameworkPrivate::activate(XhPluginContext *context)
{
    context;
}

void XhPluginFrameworkPrivate::deactivate(XhPluginContext *context)
{
    context;
}

void XhPluginFrameworkPrivate::shutdown()
{
    Locker sync(&lock);

    bool wasActive = false;
    switch (state)
    {
    case XhPlugin::INSTALLED:
    case XhPlugin::RESOLVED:
        break;
    case XhPlugin::ACTIVE:
        wasActive = true;
    case XhPlugin::STARTING:
        shutdown0(wasActive);
        break;
    case XhPlugin::STOPPING:
    case XhPlugin::UNINSTALLED:
        break;
    }
}

void XhPluginFrameworkPrivate::shutdown0(bool wasActive)
{
    {
        Locker sync(&lock);
        waitOnOperation(&lock, "Framework::stop", true);
        operation = DEACTIVATING;
        state = XhPlugin::STOPPING;
    }

    // fwCtx->listeners.emitPluginChanged(
    //       ctkPluginEvent(ctkPluginEvent::STOPPING, this->q_func()));

    if (wasActive)
    {
        stopAllPlugins();
        deactivate(this->pluginContext.data());
    }

    {
        Locker sync(&lock);
        fwCtx->uninit();
        if (state != XhPlugin::INSTALLED)
        {
            state =XhPlugin::RESOLVED;
            operation.fetchAndStoreOrdered(IDLE);
            lock.wakeAll();
        }
    }
}

void XhPluginFrameworkPrivate::stopAllPlugins()
{
    QList<QSharedPointer<XhPlugin> > activePlugins = fwCtx->plugins->getActivePlugins();
    QListIterator<QSharedPointer<XhPlugin> > it(activePlugins);
    it.toBack();
    while (it.hasPrevious())
    {
        QSharedPointer<XhPlugin> p = it.previous();
        if (p->getState() & (XhPlugin::ACTIVE | XhPlugin::STARTING))
        {
            p->stop();
        }
    }
}
