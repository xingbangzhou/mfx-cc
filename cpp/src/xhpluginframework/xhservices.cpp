#include "stable.h"
#include "xhservices.h"
#include "xhpluginframeworkcontext.h"
#include "xhserviceregistration_p.h"

#include <QList>

XhServices::XhServices(XhPluginFrameworkContext* fwCtx)
    : fwCtx(fwCtx)
{

}

XhServices::~XhServices()
{
    clear();
}

void XhServices::clear()
{
    classServices.clear();
    fwCtx = nullptr;
}

XhServiceRegistration XhServices::registerService(XhPluginPrivate *plugin,
                                                  const QString& clazz,
                                                  QObject *service)
{
    if (service == nullptr) return XhServiceRegistration();

    XhServiceRegistration reg;
    {
        QMutexLocker lock(&mutex);
        QHash<QString, XhServiceRegistration>::iterator it = classServices.find(clazz);
        if (it != classServices.end())
        {
            reg = it.value();
        }
        else
        {
            reg = XhServiceRegistration(plugin, service, clazz);
            classServices.insert(clazz, reg);
        }

        classServices.insert(clazz, reg);
    }

    XhServiceReference r = reg.getReference();
    plugin->fwCtx->listeners.serviceChanged(
                plugin->fwCtx->listeners.getMatchingServiceSlots(r),
                XhServiceEvent(XhServiceEvent::REGISTERED, r));

    return reg;
}

void XhServices::removeServiceRegistration(const XhServiceRegistration &reg)
{
    QMutexLocker lock(&mutex);

    QHash<QString, XhServiceRegistration>::iterator it = classServices.find(reg.getClazz());
    if (it != classServices.end())
    {
        if (reg == it.value())
        {
            classServices.erase(it);
        }
    }
}

XhServiceRegistration XhServices::get(const QString& clazz) const
{
    QMutexLocker lock(&mutex);
    return classServices.value(clazz);
}

QList<XhServiceRegistration> XhServices::getRegisteredByPlugin(XhPluginPrivate *p) const
{
    QMutexLocker lock(&mutex);

    QList<XhServiceRegistration> res;
    for (QHashIterator<QString, XhServiceRegistration> it(classServices); it.hasNext();)
    {
        XhServiceRegistration sr = it.next().value();
        if (sr.d_func()->plugin == p)
        {
            res.push_back(sr);
        }
    }
    return res;
}

QList<XhServiceRegistration> XhServices::getUsedByPlugin(QSharedPointer<XhPlugin> p) const
{
    QMutexLocker lock(&mutex);

    QList<XhServiceRegistration> res;
    for (QHashIterator<QString, XhServiceRegistration> it(classServices); it.hasNext();)
    {
        XhServiceRegistration sr = it.next().value();
        if (sr.d_func()->isUsedByPlugin(p))
        {
            res.push_back(sr);
        }
    }
    return res;
}
