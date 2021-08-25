#ifndef XHSERVICES_H
#define XHSERVICES_H

#include <QHash>
#include <QMutex>

#include "xhpluginframework/xhserviceregistration.h"
#include "xhplugin_p.h"

class XhPluginFrameworkContext;

class XhServices
{
public:

    mutable QMutex mutex;

    XhPluginFrameworkContext* fwCtx;

    QHash<QString, XhServiceRegistration> classServices;

    explicit XhServices(XhPluginFrameworkContext* fwCtx);
    ~XhServices();

    void clear();

    XhServiceRegistration registerService(XhPluginPrivate* plugin,
                                           const QString& clazz,
                                           QObject* service);

    void removeServiceRegistration(const XhServiceRegistration& reg);

    XhServiceRegistration get(const QString& clazz) const;

    QList<XhServiceRegistration> getRegisteredByPlugin(XhPluginPrivate* p) const;

    QList<XhServiceRegistration> getUsedByPlugin(QSharedPointer<XhPlugin> p) const;

};

#endif // XHSERVICES_H
