#ifndef XHSERVICEREGISTRATION_H
#define XHSERVICEREGISTRATION_H

#include "xhpluginfwexport.h"
#include "xhservicereference.h"
#include "xhpluginfw_global.h"

class XhServices;

class XhServiceRegistrationPrivate;

class XHPLUGINFW_EXPORT XhServiceRegistration
{
public:

    XhServiceRegistration();

    XhServiceRegistration(const XhServiceRegistration& reg);

    operator bool() const;

    XhServiceRegistration& operator=(int null);

    ~XhServiceRegistration();

    XhServiceReference getReference() const;

    QString getClazz() const;

    void unregister();

    bool operator==(const XhServiceRegistration& reg) const;

    XhServiceRegistration& operator=(const XhServiceRegistration& reg);

protected:

    friend class XhServices;
    friend class XhServiceRegistrationPrivate;

    friend uint XHPLUGINFW_EXPORT qHash(const XhServiceRegistration&);

    XhServiceRegistration(XhServiceRegistrationPrivate* registrationPrivate);

    XhServiceRegistration(XhPluginPrivate* plugin, QObject* service, const QString& clazz);

    XhServiceRegistrationPrivate* d_ptr;

private:
    Q_DECLARE_PRIVATE(XhServiceRegistration)
};

uint XHPLUGINFW_EXPORT qHash(const XhServiceRegistration& reg);

#endif // XHSERVICEREGISTRATION_H
