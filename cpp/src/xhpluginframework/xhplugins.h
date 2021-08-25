#ifndef XHPLUGINS_H
#define XHPLUGINS_H

#include <QUrl>
#include <QHash>
#include <QSharedPointer>
#include <QReadWriteLock>
#include <QMutex>

#include "xhpluginframework/xhplugin.h"

class XhPluginFrameworkContext;

class XhPlugins
{
private:

    QHash<QString, QSharedPointer<XhPlugin> > plugins;

    XhPluginFrameworkContext* fwCtx;

    mutable QReadWriteLock pluginsLock;

    QMutex objectLock;

public:
    explicit XhPlugins(XhPluginFrameworkContext* fw);

    void clear();

    QSharedPointer<XhPlugin> install(const QUrl& location);

    void remove(const QUrl& location);

    QSharedPointer<XhPlugin> getPlugin(const QString& location) const;

    QList<QSharedPointer<XhPlugin> > getPlugins() const;

    QList<QSharedPointer<XhPlugin> > getActivePlugins() const;

    void startPlugins(const QList<XhPlugin*>& slist) const;
};

#endif // XHPLUGINS_P_H
