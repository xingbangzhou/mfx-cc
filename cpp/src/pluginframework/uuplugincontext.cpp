#include "stable.h"
#include "pluginframework/uuplugincontext.h"
#include "uuplugincontext_p.h"
#include "uuplugin_p.h"
#include "uupluginframeworkcontext_p.h"

//----------------------------------------------------------------------------
uuPluginContextPrivate::uuPluginContextPrivate(uuPluginPrivate* plugin)
  : plugin(plugin)
{}

void uuPluginContextPrivate::isPluginContextValid() const
{
  if (!plugin) {
    // throw ctkIllegalStateException("This plugin context is no longer valid");
  }
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
  d->isPluginContextValid();
  return d->plugin->q_func();
}

QList<QSharedPointer<uuPlugin> > uuPluginContext::getPlugins() const
{
    Q_D(const uuPluginContext);
    d->isPluginContextValid();
    return d->plugin->fwCtx->plugins->getPlugins();
}

QSharedPointer<uuPlugin> uuPluginContext::installPlugin(const QUrl& location, QIODevice* in)
{
    Q_D(uuPluginContext);
    d->isPluginContextValid();
    return d->plugin->fwCtx->plugins->install(location, in);
}
