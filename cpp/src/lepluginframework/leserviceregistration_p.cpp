#include "stable.h"
#include "leserviceregistration_p.h"

LeServiceRegistrationPrivate::LeServiceRegistrationPrivate(
        LePluginPrivate* plugin, QObject* service, const QString& clazz)
    : ref(1), available(true), unregistering(false),
      plugin(plugin), clazz(clazz), service(service),
      reference(this)
{

}

LeServiceRegistrationPrivate::~LeServiceRegistrationPrivate()
{

}

bool LeServiceRegistrationPrivate::isUsedByPlugin(QSharedPointer<LePlugin> p)
{
    return dependents.contains(p);
}

QObject* LeServiceRegistrationPrivate::getService()
{
    return service;
}
