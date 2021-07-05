#include "stable.h"
#include "leservices.h"
#include "lepluginframeworkcontext.h"
#include "leserviceregistration_p.h"

#include <QList>

LeServices::LeServices(LePluginFrameworkContext* fwCtx)
    : fwCtx(fwCtx)
{

}

LeServices::~LeServices()
{
    clear();
}

void LeServices::clear()
{
    classServices.clear();
    fwCtx = nullptr;
}

LeServiceRegistration LeServices::registerService(LePluginPrivate *plugin,
                                                  const QString& clazz,
                                                  QObject *service)
{
    if (service == nullptr) return LeServiceRegistration();

    LeServiceRegistration reg;
    {
        QMutexLocker lock(&mutex);
        QHash<QString, LeServiceRegistration>::iterator it = classServices.find(clazz);
        if (it != classServices.end())
        {
            reg = it.value();
        }
        else
        {
            reg = LeServiceRegistration(plugin, service, clazz);
            classServices.insert(clazz, reg);
        }

        classServices.insert(clazz, reg);
    }

    LeServiceReference r = reg.getReference();
    plugin->fwCtx->listeners.serviceChanged(
                plugin->fwCtx->listeners.getMatchingServiceSlots(r),
                LeServiceEvent(LeServiceEvent::REGISTERED, r));

    return reg;
}

void LeServices::removeServiceRegistration(const LeServiceRegistration &reg)
{
    QMutexLocker lock(&mutex);

    QHash<QString, LeServiceRegistration>::iterator it = classServices.find(reg.getClazz());
    if (it != classServices.end())
    {
        if (reg == it.value())
        {
            classServices.erase(it);
        }
    }
}

LeServiceRegistration LeServices::get(const QString& clazz) const
{
    QMutexLocker lock(&mutex);
    return classServices.value(clazz);
}

QList<LeServiceRegistration> LeServices::getRegisteredByPlugin(LePluginPrivate *p) const
{
    QMutexLocker lock(&mutex);

    QList<LeServiceRegistration> res;
    for (QHashIterator<QString, LeServiceRegistration> it(classServices); it.hasNext();)
    {
        LeServiceRegistration sr = it.next().value();
        if (sr.d_func()->plugin == p)
        {
            res.push_back(sr);
        }
    }
    return res;
}

QList<LeServiceRegistration> LeServices::getUsedByPlugin(QSharedPointer<LePlugin> p) const
{
    QMutexLocker lock(&mutex);

    QList<LeServiceRegistration> res;
    for (QHashIterator<QString, LeServiceRegistration> it(classServices); it.hasNext();)
    {
        LeServiceRegistration sr = it.next().value();
        if (sr.d_func()->isUsedByPlugin(p))
        {
            res.push_back(sr);
        }
    }
    return res;
}
