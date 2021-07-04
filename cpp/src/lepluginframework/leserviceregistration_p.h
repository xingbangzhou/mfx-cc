#ifndef LESERVICEREGISTRATIONPRIVATE_H
#define LESERVICEREGISTRATIONPRIVATE_H

#include <QHash>
#include <QMutex>

#include "lepluginframework/leservicereference.h"
#include "lepluginframework/lepluginfw_global.h"

class LePluginPrivate;
class LeServiceRegistration;

class LeServiceRegistrationPrivate
{
public:

    LePluginPrivate* plugin;

    LeServiceReference reference;

    QHash<QSharedPointer<LePlugin>,int> dependents;

    QHash<QSharedPointer<LePlugin>, QObject*> serviceInstances;

    volatile bool available;

    volatile bool unregistering;

    QMutex eventLock;

    QMutex propsLock;

    LeServiceRegistrationPrivate(LePluginPrivate* plugin, QObject* service);

    ~LeServiceRegistrationPrivate();

    bool isUsedByPlugin(QSharedPointer<LePlugin> p);

    QObject* getService();

protected:

    friend class LeServiceRegistration;

    friend class LeServiceReferencePrivate;

    QAtomicInt ref;

    QObject* service;

private:

    Q_DISABLE_COPY(LeServiceRegistrationPrivate)

};

#endif // LESERVICEREGISTRATIONPRIVATE_H