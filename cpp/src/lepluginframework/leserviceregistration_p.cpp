#include "stable.h"
#include "leserviceregistration_p.h"

LeServiceRegistrationPrivate::LeServiceRegistrationPrivate(
        LePluginPrivate* plugin, QObject* service)
    : ref(1), plugin(plugin), service(service), reference(this),
      available(true), unregistering(false)
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
