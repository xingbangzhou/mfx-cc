#include "stable.h"
#include "xhserviceregistration_p.h"

XhServiceRegistrationPrivate::XhServiceRegistrationPrivate(
        XhPluginPrivate* plugin, QObject* service, const QString& clazz)
    : ref(1), available(true), unregistering(false),
      plugin(plugin), clazz(clazz), service(service),
      reference(this)
{

}

XhServiceRegistrationPrivate::~XhServiceRegistrationPrivate()
{

}

bool XhServiceRegistrationPrivate::isUsedByPlugin(QSharedPointer<XhPlugin> p)
{
    return dependents.contains(p);
}

QObject* XhServiceRegistrationPrivate::getService()
{
    return service;
}
