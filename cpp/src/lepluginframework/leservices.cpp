#include "stable.h"
#include "leservices.h"
#include "lepluginframeworkcontext.h"

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

}

LeServiceRegistration LeServices::registerService(LePluginPrivate *plugin,
                                                  const QString& className,
                                                  QObject *service)
{
    if (service == NULL) return LeServiceRegistration();

    LeServiceRegistration reg(plugin, service, className);
    {
        QMutexLocker lock(&mutex);
        regClass.insert(reg, className);
        classReg.insert(className, reg);
    }

    LeServiceReference r = reg.getReference();
    plugin->fwCtx->listeners.serviceChanged(
                plugin->fwCtx->listeners.getMatchingServiceSlots(r),
                LeServiceEvent(LeServiceEvent::REGISTERED, r));

    return reg;
}
