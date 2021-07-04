#ifndef LEPLUGINCONTEXT_H
#define LEPLUGINCONTEXT_H

#include <QSharedPointer>
#include <QIODevice>

#include "lepluginfwexport.h"

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
