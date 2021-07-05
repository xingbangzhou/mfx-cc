#ifndef LEPLUGINCONTEXT_H
#define LEPLUGINCONTEXT_H

#include <QSharedPointer>

#include "lepluginfwexport.h"
#include "leserviceregistration.h"
#include "leservicereference.h"

class LePlugin;
class LePluginPrivate;
class LePluginFrameworkPrivate;
class LePluginContextPrivate;

class LEPLUGINFW_EXPORT LePluginContext
{
public:
    ~LePluginContext();

    QSharedPointer<LePlugin> getPlugin() const;

    QList<QSharedPointer<LePlugin> > getPlugins() const;

    QSharedPointer<LePlugin> installPlugin(const QUrl& location);

    LeServiceRegistration registerService(const char* clazz, QObject* service);

    template<class S>
    LeServiceRegistration registerService(QObject* service)
    {
        const char* clazz = qobject_interface_iid<S*>();
        if (clazz == nullptr)
        {
            return LeServiceRegistration();
        }
        return registerService(clazz, service);
    }

    LeServiceReference getServiceReference(const QString& clazz);

    QObject* getService(const LeServiceReference& reference);

    template<class S>
    S* getService(const LeServiceReference& reference)
    {
        return qobject_cast<S*>(getService(reference));
    }

    bool ungetService(const LeServiceReference& reference);

    void connectServiceListener(QObject* receiver, const char* slot);

    void disconnectServiceListener(QObject* receiver, const char* slot);

protected:
    friend class LePlugin;
    friend class LePluginPrivate;
    friend class LePluginFrameworkPrivate;

    explicit LePluginContext(LePluginPrivate* plugin);

    LePluginContextPrivate* const d_ptr;

private:
   Q_DECLARE_PRIVATE(LePluginContext);
};

#endif // LEPLUGINCONTEXT_H
