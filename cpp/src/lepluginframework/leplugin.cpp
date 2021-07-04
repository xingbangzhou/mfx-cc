﻿#include "stable.h"
#include "lepluginframework/leplugin.h"
#include "leplugin_p.h"
#include "lepluginframework/leplugincontext.h"
#include "lepluginframeworkcontext.h"

LePlugin::LePlugin() : d_ptr(NULL), logger("LePlugin")
{

}

LePlugin::~LePlugin()
{
    Q_ASSERT(d_ptr);
    delete d_ptr;
}

void LePlugin::init(LePluginPrivate* dd)
{
    Q_ASSERT(!d_ptr);
    d_ptr = dd;
}

void LePlugin::init(const QWeakPointer<LePlugin> &self, LePluginFrameworkContext *fw, const QString &loc)
{
    Q_ASSERT(!d_ptr);
    d_ptr = new LePluginPrivate(self, fw, loc);
}

LePlugin::State LePlugin::getState() const
{
  Q_D(const LePlugin);
  return d->state;
}

void LePlugin::start()
{
    Q_D(LePlugin);

    if (d->state == UNINSTALLED)
    {
        logger.error(d->location + " is uninstalled");
        return;
    }

    if (d->state == ACTIVE)
    {
        logger.info(d->location + " is active");
        return;
    }
    // resolve plugin
    d->getUpdatedState();

    d->finalizeActivation();
}

void LePlugin::stop()
{
    Q_D(LePlugin);

    if (d->state == UNINSTALLED)
    {
        return; //throw ctkIllegalStateException("ctkPlugin is uninstalled");
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

void LePlugin::uninstall()
{
    Q_D(LePlugin);

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
        d->operation.fetchAndStoreOrdered(LePluginPrivate::UNINSTALLING);
    }
    case RESOLVED:
    case INSTALLED:
    {
        d->fwCtx->plugins->remove(d->location);
        if (d->operation.fetchAndAddOrdered(0) != LePluginPrivate::UNINSTALLING)
        {
            d->waitOnOperation(&d->operationLock, "Plugin::uninstall", true);
            d->operation.fetchAndStoreOrdered(LePluginPrivate::UNINSTALLING);
        }

        // d->fwCtx->listeners.emitPluginChanged(ctkPluginEvent(ctkPluginEvent::UNRESOLVED, d->q_func()));
        d->pluginActivator = 0;
        d->state = UNINSTALLED;
        d->operation.fetchAndStoreOrdered(LePluginPrivate::IDLE);
        d->operationLock.wakeAll();
        break;
    }
    }
    // d->fwCtx->listeners.emitPluginChanged(ctkPluginEvent(ctkPluginEvent::UNINSTALLED, d->q_ptr));
}

LePluginContext* LePlugin::getPluginContext() const
{
    Q_D(const LePlugin);
    return d->pluginContext.data();
}

QString LePlugin::getLocation() const
{
  Q_D(const LePlugin);
  return d->location;
}