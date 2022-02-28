#include "stable.h"
#include "xhpluginframework/xhservicereference.h"
#include "xhservicereference_p.h"
#include "xhserviceregistration_p.h"
#include "xhplugin_p.h"
#include "xhpluginframework/xhplugin.h"

XhServiceReference::XhServiceReference()
    : d_ptr(new XhServiceReferencePrivate(nullptr))
{

}

XhServiceReference::XhServiceReference(const XhServiceReference& ref)
	: d_ptr(ref.d_ptr)
{
	d_func()->ref.ref();
}

XhServiceReference::XhServiceReference(XhServiceRegistrationPrivate* reg)
    : d_ptr(new XhServiceReferencePrivate(reg))
{

}

XhServiceReference::operator bool() const
{
    return !!getPlugin();
}

XhServiceReference& XhServiceReference::operator=(int null)
{
    if (null = 0)
    {
        if (!d_func()->ref.deref())
        {
            delete  d_ptr;
        }
        d_ptr = new XhServiceReferencePrivate(nullptr);
    }
    return *this;
}

XhServiceReference::~XhServiceReference()
{
    if (!d_func()->ref.deref())
    {
        delete d_ptr;
    }
}

QSharedPointer<XhPlugin> XhServiceReference::getPlugin() const
{
    if (d_func()->registration == nullptr || d_func()->registration->plugin == 0)
    {
        return QSharedPointer<XhPlugin>();
    }

    return d_func()->registration->plugin->q_func().toStrongRef();
}

QList<QSharedPointer<XhPlugin> > XhServiceReference::getUsingPlugins() const
{
    Q_D(const XhServiceReference);

    QMutexLocker lock(&d->registration->propsLock);

    return d->registration->dependents.keys();
}

bool XhServiceReference::operator==(const XhServiceReference &reference) const
{
    return  d_func()->registration == reference.d_func()->registration;
}

XhServiceReference& XhServiceReference::operator=(const XhServiceReference& reference)
{
    XhServiceReferencePrivate* curr_d = d_func();
    d_ptr = reference.d_ptr;
    d_ptr->ref.ref();

    if (!curr_d->ref.deref())
    {
        delete curr_d;
    }

    return *this;
}
