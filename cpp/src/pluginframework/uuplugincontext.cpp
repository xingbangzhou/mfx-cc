#include "stable.h"
#include "pluginframework/uuplugincontext.h"
#include "uuplugin_p.h"
#include "uupluginframeworkcontext.h"
#include "uuplugincontext_p.h"

//----------------------------------------------------------------------------
uuPluginContextPrivate::uuPluginContextPrivate(uuPluginPrivate* plugin)
    : plugin(plugin)
{

}

void uuPluginContextPrivate::invalidate()
{
    plugin = NULL;
}

//----------------------------------------------------------------------------
uuPluginContext::uuPluginContext(uuPluginPrivate* plugin)
    : d_ptr(new uuPluginContextPrivate(plugin))
{}

uuPluginContext::~uuPluginContext()
{
    Q_D(uuPluginContext);
    delete d;
}

QSharedPointer<uuPlugin> uuPluginContext::getPlugin() const
{
    Q_D(const uuPluginContext);
    return d->plugin->q_func();
}

QList<QSharedPointer<uuPlugin> > uuPluginContext::getPlugins() const
{
    Q_D(const uuPluginContext);
    return d->plugin->fwCtx->plugins->getPlugins();
}

QSharedPointer<uuPlugin> uuPluginContext::installPlugin(const QUrl& location)
{
    Q_D(uuPluginContext);
    return d->plugin->fwCtx->plugins->install(location);
}
