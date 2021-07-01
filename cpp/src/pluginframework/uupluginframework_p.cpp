#include "stable.h"
#include "uupluginframework_p.h"
#include "pluginframework/uuplugin_constants.h"
#include "uupluginframeworkcontext.h"
#include "pluginframework/uuplugincontext.h"
#include "uuplugincontext_p.h"

uuPluginFrameworkPrivate::uuPluginFrameworkPrivate(QWeakPointer<uuPlugin> qq, uuPluginFrameworkContext* fw)
    : uuPluginPrivate(qq, fw, uuPluginConstants::SYSTEM_PLUGIN_LOCATION)
{

}

void uuPluginFrameworkPrivate::init()
{
    this->state = uuPlugin::STARTING;
    this->fwCtx->init();
}

void uuPluginFrameworkPrivate::initSystemPlugin()
{
    this->pluginContext.reset(new uuPluginContext(this));
}

void uuPluginFrameworkPrivate::uninitSystemPlugin()
{
    this->pluginContext->d_func()->invalidate();
}

void uuPluginFrameworkPrivate::activate(uuPluginContext *context)
{
    context;
}

void uuPluginFrameworkPrivate::deactivate(uuPluginContext *context)
{
    context;
}

void uuPluginFrameworkPrivate::shutdown()
{
    Locker sync(&lock);

    bool wasActive = false;
    switch (state)
    {
    case uuPlugin::INSTALLED:
    case uuPlugin::RESOLVED:
        break;
    case uuPlugin::ACTIVE:
        wasActive = true;
    case uuPlugin::STARTING:
        shutdown0(wasActive);
        break;
    case uuPlugin::STOPPING:
    case uuPlugin::UNINSTALLED:
        break;
    }
}

void uuPluginFrameworkPrivate::shutdown0(bool wasActive)
{
    {
        Locker sync(&lock);
        waitOnOperation(&lock, "Framework::stop", true);
        operation = DEACTIVATING;
        state = uuPlugin::STOPPING;
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
        if (state != uuPlugin::INSTALLED)
        {
            state =uuPlugin::RESOLVED;
            operation.fetchAndStoreOrdered(IDLE);
            lock.wakeAll();
        }
    }
}

void uuPluginFrameworkPrivate::stopAllPlugins()
{
    QList<QSharedPointer<uuPlugin> > activePlugins = fwCtx->plugins->getActivePlugins();
    QListIterator<QSharedPointer<uuPlugin> > it(activePlugins);
    it.toBack();
    while (it.hasPrevious())
    {
        QSharedPointer<uuPlugin> p = it.previous();
        if (p->getState() & (uuPlugin::ACTIVE | uuPlugin::STARTING))
        {
            p->stop();
        }
    }
}
