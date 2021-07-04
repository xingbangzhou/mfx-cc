#include "stable.h"
#include "lepluginframework/leserviceregistration.h"
#include "leserviceregistration_p.h"
#include "leplugin_p.h"
#include "lepluginframeworkcontext.h"
#include "leservices.h"

LeServiceRegistration::LeServiceRegistration()
    : d_ptr(NULL)
{

}

LeServiceRegistration::LeServiceRegistration(const LeServiceRegistration& reg)
    : d_ptr(reg.d_ptr)
{
    if (d_func())
    {
        d_func()->ref.ref();
    }
}

LeServiceRegistration::LeServiceRegistration(LeServiceRegistrationPrivate* registrationPrivate)
  : d_ptr(registrationPrivate)
{
    if(d_func())
    {
        d_func()->ref.ref();
    }
}

LeServiceRegistration::LeServiceRegistration(LePluginPrivate* plugin, QObject* service)
  : d_ptr(new LeServiceRegistrationPrivate(plugin, service))
{

}

LeServiceRegistration::operator bool() const
{
    return d_func();
}

LeServiceRegistration& LeServiceRegistration::operator=(int null)
{
    if (null == 0)
    {
        if (d_func() && !d_func()->ref.deref())
        {
            delete d_ptr;
        }
        d_ptr = 0;
    }
    return *this;
}

LeServiceRegistration::~LeServiceRegistration()
{
    if (d_func() && !d_func()->ref.deref())
    {
        delete d_ptr;
    }
}

LeServiceReference LeServiceRegistration::getReference() const
{
  Q_D(const LeServiceRegistration);

  return d->reference;
}

void LeServiceRegistration::unregister()
{
    Q_D(LeServiceRegistration);
    if (!d) return;

    if (d->unregistering) return;
    {
        QMutexLocker lock(&d->eventLock);
        if (d->unregistering) return;
        d->unregistering = true;

        if (d->available)
        {
            if (d->plugin)
            {
                d->plugin->fwCtx->services->removeServiceRegistration(*this);
            }
        }
    }

    if (d->plugin)
    {
        d->plugin->fwCtx->listeners.serviceChanged(
                    d->plugin->fwCtx->listeners.getMatchingServiceSlots(d->reference),
                    LeServiceEvent(LeServiceEvent::UNREGISTERING, d->reference));
    }

    {
        QMutexLocker lock(&d->propsLock);
        d->available = false;
        d->plugin = 0;
        d->dependents.clear();
        d->service = 0;
        d->serviceInstances.clear();
        d->reference = 0;
        d->unregistering = false;
    }
}
