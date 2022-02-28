#include "stable.h"
#include "xhpluginframework/xhserviceregistration.h"
#include "xhserviceregistration_p.h"
#include "xhplugin_p.h"
#include "xhpluginframeworkcontext.h"
#include "xhservices.h"

XhServiceRegistration::XhServiceRegistration()
    : d_ptr(nullptr)
{

}

XhServiceRegistration::XhServiceRegistration(const XhServiceRegistration& reg)
    : d_ptr(reg.d_ptr)
{
    if (d_func())
    {
        d_func()->ref.ref();
    }
}

XhServiceRegistration::XhServiceRegistration(XhServiceRegistrationPrivate* registrationPrivate)
  : d_ptr(registrationPrivate)
{
    if(d_func())
    {
        d_func()->ref.ref();
    }
}

XhServiceRegistration::XhServiceRegistration(XhPluginPrivate* plugin, QObject* service, const QString& clazz)
  : d_ptr(new XhServiceRegistrationPrivate(plugin, service, clazz))
{

}

XhServiceRegistration::operator bool() const
{
    return d_func();
}

XhServiceRegistration& XhServiceRegistration::operator=(int null)
{
    if (null == 0)
    {
        if (d_func() && !d_func()->ref.deref())
        {
            delete d_ptr;
        }
        d_ptr = nullptr;
    }
    return *this;
}

XhServiceRegistration::~XhServiceRegistration()
{
    if (d_func() && !d_func()->ref.deref())
    {
        delete d_ptr;
    }
}

XhServiceReference XhServiceRegistration::getReference() const
{
  Q_D(const XhServiceRegistration);

  return d->reference;
}

QString XhServiceRegistration::getClazz() const
{
    Q_D(const XhServiceRegistration);

    return d->clazz;
}

void XhServiceRegistration::unregister()
{
    Q_D(XhServiceRegistration);
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
                    XhServiceEvent(XhServiceEvent::UNREGISTERING, d->reference));
    }

    {
        QMutexLocker lock(&d->propsLock);
        d->available = false;
        d->plugin = 0;
        d->dependents.clear();
        d->service = 0;
        d->reference = 0;
        d->unregistering = false;
    }
}

bool XhServiceRegistration::operator==(const XhServiceRegistration &reg) const
{
    Q_D(const XhServiceRegistration);
    return d == reg.d_func();
}

XhServiceRegistration& XhServiceRegistration::operator=(const XhServiceRegistration &reg)
{
    XhServiceRegistrationPrivate* curr_d = d_func();
    d_ptr = reg.d_ptr;
    if (d_ptr)
    {
        d_ptr->ref.ref();
    }

    if (curr_d && !curr_d->ref.deref())
    {
        delete curr_d;
    }

    return *this;
}

size_t qHash(const XhServiceRegistration& reg)
{
    return qHash(reg.d_func());
}
