#include "stable.h"
#include "xhpluginframework/xhplugin.h"
#include "xhplugin_p.h"
#include "xhpluginframework/xhplugincontext.h"
#include "xhpluginframeworkcontext.h"

XhPlugin::XhPlugin() : d_ptr(nullptr)
{

}

XhPlugin::~XhPlugin()
{
    Q_ASSERT(d_ptr);
    delete d_ptr;
}

void XhPlugin::init(XhPluginPrivate* dd)
{
    Q_ASSERT(!d_ptr);
    d_ptr = dd;
}

void XhPlugin::init(const QWeakPointer<XhPlugin> &self, XhPluginFrameworkContext *fw, const QString &loc)
{
    Q_ASSERT(!d_ptr);
    d_ptr = new XhPluginPrivate(self, fw, loc);
}

XhPlugin::State XhPlugin::getState() const
{
  Q_D(const XhPlugin);
  return d->state;
}

void XhPlugin::start()
{
    Q_D(XhPlugin);

    if (d->state == UNINSTALLED)
    {
		d->fwCtx->logger().error(d->location + "[start]: UNINSTALLED");
        return;
    }

    if (d->state == ACTIVE)
    {
		d->fwCtx->logger().warn(d->location + "[start]: ALREADY ACTIVE");
        return;
    }
    // resolve plugin
    d->getUpdatedState();

    d->finalizeActivation();
}

void XhPlugin::stop()
{
    Q_D(XhPlugin);

    if (d->state == UNINSTALLED)
    {
        return;
    }

    d->waitOnOperation(&d->operationLock, "Plugin::stop", false);

    switch (d->state)
    {
    case INSTALLED:
    case RESOLVED:
    case STOPPING:
    case UNINSTALLED:
        return;
    case ACTIVE:
    case STARTING:
        d->stop0();
        break;
    }
}

void XhPlugin::uninstall()
{
    Q_D(XhPlugin);

    switch (d->state)
    {
    case UNINSTALLED:
        return;
    case STARTING:
    case ACTIVE:
    case STOPPING:
    {
        d->waitOnOperation(&d->operationLock, "ctkPlugin::uninstall", true);
        if (d->state & (ACTIVE | STARTING))
        {
            d->stop0();
        }
        d->operation.fetchAndStoreOrdered(XhPluginPrivate::UNINSTALLING);
    }
    case RESOLVED:
    case INSTALLED:
    {
        d->fwCtx->plugins->remove(d->location);
        if (d->operation.fetchAndAddOrdered(0) != XhPluginPrivate::UNINSTALLING)
        {
            d->waitOnOperation(&d->operationLock, "Plugin::uninstall", true);
            d->operation.fetchAndStoreOrdered(XhPluginPrivate::UNINSTALLING);
        }

        d->pluginActivator = 0;
        d->state = UNINSTALLED;
        d->operation.fetchAndStoreOrdered(XhPluginPrivate::IDLE);
        d->operationLock.wakeAll();
        break;
    }
	}
}

XhPluginContext* XhPlugin::getPluginContext() const
{
    Q_D(const XhPlugin);
    return d->pluginContext.data();
}

QString XhPlugin::getLocation() const
{
  Q_D(const XhPlugin);
  return d->location;
}
