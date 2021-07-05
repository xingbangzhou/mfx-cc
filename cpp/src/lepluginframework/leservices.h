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

    QHash<QString, LeServiceRegistration> classServices;

    explicit LeServices(LePluginFrameworkContext* fwCtx);
    ~LeServices();

    void clear();

    LeServiceRegistration registerService(LePluginPrivate* plugin,
                                           const QString& clazz,
                                           QObject* service);

    void removeServiceRegistration(const LeServiceRegistration& reg);

    LeServiceRegistration get(const QString& clazz) const;

    QList<LeServiceRegistration> getRegisteredByPlugin(LePluginPrivate* p) const;

    QList<LeServiceRegistration> getUsedByPlugin(QSharedPointer<LePlugin> p) const;

};

#endif // LESERVICES_H
