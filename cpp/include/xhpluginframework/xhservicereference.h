#ifndef XHSERVICEREFERENCE_H
#define XHSERVICEREFERENCE_H

#include <QVariant>

#include "xhpluginfwexport.h"
#include "xhplugin.h"

class XhServiceRegistrationPrivate;
class XhServiceReferencePrivate;
class XhPluginPrivate;
class XhPluginContext;

class XHPLUGINFW_EXPORT XhServiceReference
{
public:

    XhServiceReference();

    XhServiceReference(const XhServiceReference& ref);

    operator bool() const;

    XhServiceReference& operator=(int null);

    ~XhServiceReference();

    QSharedPointer<XhPlugin> getPlugin() const;

    QList<QSharedPointer<XhPlugin> > getUsingPlugins() const;

    bool operator==(const XhServiceReference& reference) const;

    XhServiceReference& operator=(const XhServiceReference& reference);

protected:
    friend class XhServiceRegistrationPrivate;
    friend class XhPluginPrivate;
    friend class XhPluginContext;

    friend uint XHPLUGINFW_EXPORT qHash(const XhServiceReference&);

    XhServiceReference(XhServiceRegistrationPrivate* reg);

    XhServiceReferencePrivate * d_ptr;

private:
  Q_DECLARE_PRIVATE(XhServiceReference)
};

uint XHPLUGINFW_EXPORT qHash(const XhServiceReference& srf);

Q_DECLARE_METATYPE(XhServiceReference)

#endif // XHSERVICEREFERENCE_H
