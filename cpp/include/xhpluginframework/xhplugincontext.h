#ifndef XHPLUGINCONTEXT_H
#define XHPLUGINCONTEXT_H

#include <QSharedPointer>

#include "xhpluginfwexport.h"
#include "xhserviceregistration.h"
#include "xhservicereference.h"

class XhPlugin;
class XhPluginPrivate;
class XhPluginFrameworkPrivate;
class XhPluginContextPrivate;

class XHPLUGINFW_EXPORT XhPluginContext
{
public:
    ~XhPluginContext();

    QSharedPointer<XhPlugin> getPlugin() const;

    QList<QSharedPointer<XhPlugin> > getPlugins() const;

    QSharedPointer<XhPlugin> installPlugin(const QUrl& location);

    XhServiceRegistration registerService(const char* clazz, QObject* service);

    template<class S>
    XhServiceRegistration registerService(QObject* service)
    {
        const char* clazz = qobject_interface_iid<S*>();
        if (clazz == nullptr)
        {
            return XhServiceRegistration();
        }
        return registerService(clazz, service);
    }

    XhServiceReference getServiceReference(const QString& clazz);

    QObject* getService(const XhServiceReference& reference);

    template<class S>
    S* getService(const XhServiceReference& reference)
    {
        return qobject_cast<S*>(getService(reference));
    }

    bool ungetService(const XhServiceReference& reference);

    void connectServiceListener(QObject* receiver, const char* slot);

    void disconnectServiceListener(QObject* receiver, const char* slot);

protected:
    friend class XhPlugin;
    friend class XhPluginPrivate;
    friend class XhPluginFrameworkPrivate;

    explicit XhPluginContext(XhPluginPrivate* plugin);

    XhPluginContextPrivate* const d_ptr;

private:
   Q_DECLARE_PRIVATE(XhPluginContext);
};

#endif // XHPLUGINCONTEXT_H
