#include "stable.h"
#include "lepluginframework/leservicereference.h"
#include "leservicereference_p.h"
#include "leserviceregistration_p.h"
#include "leplugin_p.h"
#include "lepluginframework/leplugin.h"

LeServiceReference::LeServiceReference()
    : d_ptr(new LeServiceReferencePrivate(nullptr))
{

}

LeServiceReference::LeServiceReference(const LeServiceReference& ref)
	: d_ptr(ref.d_ptr)
{
	d_func()->ref.ref();
}

LeServiceReference::LeServiceReference(LeServiceRegistrationPrivate* reg)
    : d_ptr(new LeServiceReferencePrivate(reg))
{

}

LeServiceReference::operator bool() const
{
    return getPlugin();
}

LeServiceReference& LeServiceReference::operator=(int null)
{
    if (null = 0)
    {
        if (!d_func()->ref.deref())
        {
            delete  d_ptr;
        }
        d_ptr = new LeServiceReferencePrivate(nullptr);
    }
    return *this;
}

LeServiceReference::~LeServiceReference()
{
    if (!d_func()->ref.deref())
    {
        delete d_ptr;
    }
}

QSharedPointer<LePlugin> LeServiceReference::getPlugin() const
{
    if (d_func()->registration == nullptr || d_func()->registration->plugin == 0)
    {
        return QSharedPointer<LePlugin>();
    }

    return d_func()->registration->plugin->q_func().toStrongRef();
}

QList<QSharedPointer<LePlugin> > LeServiceReference::getUsingPlugins() const
{
    Q_D(const LeServiceReference);

    QMutexLocker lock(&d->registration->propsLock);

    return d->registration->dependents.keys();
}

bool LeServiceReference::operator==(const LeServiceReference &reference) const
{
    return  d_func()->registration == reference.d_func()->registration;
}

LeServiceReference& LeServiceReference::operator=(const LeServiceReference& reference)
{
    LeServiceReferencePrivate* curr_d = d_func();
    d_ptr = reference.d_ptr;
    d_ptr->ref.ref();

    if (!curr_d->ref.deref())
    {
        delete curr_d;
    }

    return *this;
}
