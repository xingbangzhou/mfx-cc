#include "stable.h"
#include "lepluginframework/leplugincontext.h"
#include "leplugin_p.h"
#include "lepluginframeworkcontext.h"
#include "leplugincontext_p.h"
#include "leservices.h"
#include "leservicereference_p.h"

//----------------------------------------------------------------------------
LePluginContextPrivate::LePluginContextPrivate(LePluginPrivate* plugin)
    : plugin(plugin)
{

}

bool LePluginContextPrivate::isPluginContextValid() const
{
    return plugin != nullptr;
}

void LePluginContextPrivate::invalidate()
{
    plugin = nullptr;
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

LeServiceRegistration LePluginContext::registerService(const char* clazz, QObject* service)
{
    Q_D(LePluginContext);
	Q_ASSERT(d->isPluginContextValid());
    
	return d->plugin->fwCtx->services->registerService(d->plugin, clazz, service);
}

LeServiceReference LePluginContext::getServiceReference(const QString& clazz)
{
    Q_D(LePluginContext);
	Q_ASSERT(d->isPluginContextValid());
    
    return d->plugin->fwCtx->services->get(clazz).getReference();
}

QObject* LePluginContext::getService(const LeServiceReference& reference)
{
	if (!reference) return nullptr;
	
    Q_D(LePluginContext);
	Q_ASSERT(d->isPluginContextValid());
	
    LeServiceReference ref(reference);
    return ref.d_func()->getService(d->plugin->q_func());
}

bool LePluginContext::ungetService(const LeServiceReference& reference)
{
    Q_D(LePluginContext);
	Q_ASSERT(d->isPluginContextValid());

    LeServiceReference ref = reference;
    return ref.d_func()->ungetService(d->plugin->q_func(), true);
}

void LePluginContext::connectServiceListener(QObject* receiver, const char* slot)
{
    Q_D(LePluginContext);
	Q_ASSERT(d->isPluginContextValid());

    d->plugin->fwCtx->listeners.addServiceSlot(getPlugin(), receiver, slot);
}

void LePluginContext::disconnectServiceListener(QObject* receiver, const char* slot)
{
    Q_D(LePluginContext);
	Q_ASSERT(d->isPluginContextValid());

    d->plugin->fwCtx->listeners.removeServiceSlot(getPlugin(), receiver, slot);
}
