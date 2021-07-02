#include "stable.h"
#include "lepluginframework/leplugincontext.h"
#include "leplugin_p.h"
#include "lepluginframeworkcontext.h"
#include "leplugincontext_p.h"

//----------------------------------------------------------------------------
LePluginContextPrivate::LePluginContextPrivate(LePluginPrivate* plugin)
    : plugin(plugin)
{

}

void LePluginContextPrivate::invalidate()
{
    plugin = NULL;
}

//----------------------------------------------------------------------------
LePluginContext::LePluginContext(LePluginPrivate* plugin)
    : d_ptr(new LePluginContextPrivate(plugin))
{}

LePluginContext::~LePluginContext()
{
    Q_D(LePluginContext);
    delete d;
}

QSharedPointer<LePlugin> LePluginContext::getPlugin() const
{
    Q_D(const LePluginContext);
    return d->plugin->q_func();
}

QList<QSharedPointer<LePlugin> > LePluginContext::getPlugins() const
{
    Q_D(const LePluginContext);
    return d->plugin->fwCtx->plugins->getPlugins();
}

QSharedPointer<LePlugin> LePluginContext::installPlugin(const QUrl& location)
{
    Q_D(LePluginContext);
    return d->plugin->fwCtx->plugins->install(location);
}
