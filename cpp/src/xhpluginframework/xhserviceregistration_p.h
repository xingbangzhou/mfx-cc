#ifndef XHSERVICEREGISTRATIONPRIVATE_H
#define XHSERVICEREGISTRATIONPRIVATE_H

#include <QHash>
#include <QMutex>

#include "xhpluginframework/xhservicereference.h"
#include "xhpluginframework/xhpluginfw_global.h"

class XhPluginPrivate;
class XhServiceRegistration;

class XhServiceRegistrationPrivate
{
public:

    XhPluginPrivate* plugin;

    XhServiceReference reference;

    const QString clazz;

    QHash<QSharedPointer<XhPlugin>,int> dependents;

    volatile bool available;

    volatile bool unregistering;

    QMutex eventLock;

    QMutex propsLock;

    XhServiceRegistrationPrivate(XhPluginPrivate* plugin, QObject* service, const QString& clazz);

    ~XhServiceRegistrationPrivate();

    bool isUsedByPlugin(QSharedPointer<XhPlugin> p);

    QObject* getService();

protected:

    friend class XhServiceRegistration;

    friend class XhServiceReferencePrivate;

    QAtomicInt ref;

    QObject* service;

private:

    Q_DISABLE_COPY(XhServiceRegistrationPrivate)

};

#endif // XHSERVICEREGISTRATIONPRIVATE_H
