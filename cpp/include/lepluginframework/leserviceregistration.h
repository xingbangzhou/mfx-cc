#ifndef LESERVICEREGISTRATION_H
#define LESERVICEREGISTRATION_H

#include "lepluginfwexport.h"
#include "leservicereference.h"
#include "lepluginfw_global.h"

class LeServices;

class LeServiceRegistrationPrivate;

class LEPLUGINFW_EXPORT LeServiceRegistration
{
public:

    LeServiceRegistration();

    LeServiceRegistration(const LeServiceRegistration& reg);

    operator bool() const;

    LeServiceRegistration& operator=(int null);

    ~LeServiceRegistration();

    LeServiceReference getReference() const;

    QString getClazz() const;

    void unregister();

    bool operator==(const LeServiceRegistration& reg) const;

    LeServiceRegistration& operator=(const LeServiceRegistration& reg);

protected:

    friend class LeServices;
    friend class LeServiceRegistrationPrivate;

    friend uint LEPLUGINFW_EXPORT qHash(const LeServiceRegistration&);

    LeServiceRegistration(LeServiceRegistrationPrivate* registrationPrivate);

    LeServiceRegistration(LePluginPrivate* plugin, QObject* service, const QString& clazz);

    LeServiceRegistrationPrivate* d_ptr;

private:
    Q_DECLARE_PRIVATE(LeServiceRegistration)
};

uint LEPLUGINFW_EXPORT qHash(const LeServiceRegistration& reg);

#endif // LESERVICEREGISTRATION_H
