#include "stable.h"
#include "xhpluginframework/xhplugincontext.h"
#include "xhplugin_p.h"
#include "xhpluginframeworkcontext.h"
#include "xhplugincontext_p.h"
#include "xhservices.h"
#include "xhservicereference_p.h"

//----------------------------------------------------------------------------
XhPluginContextPrivate::XhPluginContextPrivate(XhPluginPrivate* plugin)
    : plugin(plugin)
{

}

bool XhPluginContextPrivate::isPluginContextValid() const
{
    return plugin != nullptr;
}

void XhPluginContextPrivate::invalidate()
{
    plugin = nullptr;
}

//----------------------------------------------------------------------------
XhPluginContext::XhPluginContext(XhPluginPrivate* plugin)
    : d_ptr(new XhPluginContextPrivate(plugin))
{}

XhPluginContext::~XhPluginContext()
{
    Q_D(XhPluginContext);
    delete d;
}

QSharedPointer<XhPlugin> XhPluginContext::getPlugin() const
{
    Q_D(const XhPluginContext);
    return d->plugin->q_func();
}

QList<QSharedPointer<XhPlugin> > XhPluginContext::getPlugins() const
{
    Q_D(const XhPluginContext);
    return d->plugin->fwCtx->plugins->getPlugins();
}

QSharedPointer<XhPlugin> XhPluginContext::installPlugin(const QUrl& location)
{
    Q_D(XhPluginContext);
    return d->plugin->fwCtx->plugins->install(location);
}

XhServiceRegistration XhPluginContext::registerService(const char* clazz, QObject* service)
{
    Q_D(XhPluginContext);
	Q_ASSERT(d->isPluginContextValid());
    
	return d->plugin->fwCtx->services->registerService(d->plugin, clazz, service);
}

XhServiceReference XhPluginContext::getServiceReference(const QString& clazz)
{
    Q_D(XhPluginContext);
	Q_ASSERT(d->isPluginContextValid());
    
    return d->plugin->fwCtx->services->get(clazz).getReference();
}

QObject* XhPluginContext::getService(const XhServiceReference& reference)
{
	if (!reference) return nullptr;
	
    Q_D(XhPluginContext);
	Q_ASSERT(d->isPluginContextValid());
	
    XhServiceReference ref(reference);
    return ref.d_func()->getService(d->plugin->q_func());
}

bool XhPluginContext::ungetService(const XhServiceReference& reference)
{
    Q_D(XhPluginContext);
	Q_ASSERT(d->isPluginContextValid());

    XhServiceReference ref = reference;
    return ref.d_func()->ungetService(d->plugin->q_func(), true);
}

void XhPluginContext::connectServiceListener(QObject* receiver, const char* slot)
{
    Q_D(XhPluginContext);
	Q_ASSERT(d->isPluginContextValid());

    d->plugin->fwCtx->listeners.addServiceSlot(getPlugin(), receiver, slot);
}

void XhPluginContext::disconnectServiceListener(QObject* receiver, const char* slot)
{
    Q_D(XhPluginContext);
	Q_ASSERT(d->isPluginContextValid());

    d->plugin->fwCtx->listeners.removeServiceSlot(getPlugin(), receiver, slot);
}
