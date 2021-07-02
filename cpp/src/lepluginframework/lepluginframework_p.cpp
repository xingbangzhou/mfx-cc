#include "stable.h"
#include "lepluginframework_p.h"
#include "lepluginframework/leplugin_constants.h"
#include "lepluginframeworkcontext.h"
#include "lepluginframework/leplugincontext.h"
#include "leplugincontext_p.h"

LePluginFrameworkPrivate::LePluginFrameworkPrivate(QWeakPointer<LePlugin> qq, LePluginFrameworkContext* fw)
    : LePluginPrivate(qq, fw, LePluginConstants::SYSTEM_PLUGIN_LOCATION)
{

}

void LePluginFrameworkPrivate::init()
{
    this->state = LePlugin::STARTING;
    this->fwCtx->init();
}

void LePluginFrameworkPrivate::initSystemPlugin()
{
    this->pluginContext.reset(new LePluginContext(this));
}

void LePluginFrameworkPrivate::uninitSystemPlugin()
{
    this->pluginContext->d_func()->invalidate();
}

void LePluginFrameworkPrivate::activate(LePluginContext *context)
{
    context;
}

void LePluginFrameworkPrivate::deactivate(LePluginContext *context)
{
    context;
}

void LePluginFrameworkPrivate::shutdown()
{
    Locker sync(&lock);

    bool wasActive = false;
    switch (state)
    {
    case LePlugin::INSTALLED:
    case LePlugin::RESOLVED:
        break;
    case LePlugin::ACTIVE:
        wasActive = true;
    case LePlugin::STARTING:
        shutdown0(wasActive);
        break;
    case LePlugin::STOPPING:
    case LePlugin::UNINSTALLED:
        break;
    }
}

void LePluginFrameworkPrivate::shutdown0(bool wasActive)
{
    {
        Locker sync(&lock);
        waitOnOperation(&lock, "Framework::stop", true);
        operation = DEACTIVATING;
        state = LePlugin::STOPPING;
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
        if (state != LePlugin::INSTALLED)
        {
            state =LePlugin::RESOLVED;
            operation.fetchAndStoreOrdered(IDLE);
            lock.wakeAll();
        }
    }
}

void LePluginFrameworkPrivate::stopAllPlugins()
{
    QList<QSharedPointer<LePlugin> > activePlugins = fwCtx->plugins->getActivePlugins();
    QListIterator<QSharedPointer<LePlugin> > it(activePlugins);
    it.toBack();
    while (it.hasPrevious())
    {
        QSharedPointer<LePlugin> p = it.previous();
        if (p->getState() & (LePlugin::ACTIVE | LePlugin::STARTING))
        {
            p->stop();
        }
    }
}
