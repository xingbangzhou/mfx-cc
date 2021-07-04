#ifndef LESERVICES_H
#define LESERVICES_H

#include <QHash>
#include <QMutex>

#include "lepluginframework/leserviceregistration.h"
#include "leplugin_p.h"

class LePluginFrameworkContext;

class LeServices
{
public:

    mutable QMutex mutex;

    LePluginFrameworkContext* fwCtx;

    QHash<LeServiceRegistration, QString> regClass;

    QHash<QString, LeServiceRegistration> classReg;

    explicit LeServices(LePluginFrameworkContext* fwCtx);
    ~LeServices();

    void clear();

    LeServiceRegistration registerService(LePluginPrivate* plugin,
                                           const QString& className,
                                           QObject* service);

    void removeServiceRegistration(const LeServiceRegistration& reg);
};

#endif // LESERVICES_H
