#ifndef LEPLUGINS_H
#define LEPLUGINS_H

#include <QUrl>
#include <QHash>
#include <QSharedPointer>
#include <QReadWriteLock>
#include <QMutex>
#include <QIODevice>

#include "lepluginframework/leplugin.h"

class LePluginFrameworkContext;

class LePlugins
{
private:

    QHash<QString, QSharedPointer<LePlugin> > plugins;

    LePluginFrameworkContext* fwCtx;

    mutable QReadWriteLock pluginsLock;

    QMutex objectLock;

public:
    explicit LePlugins(LePluginFrameworkContext* fw);

    void clear();

    QSharedPointer<LePlugin> install(const QUrl& location);

    void remove(const QUrl& location);

    QSharedPointer<LePlugin> getPlugin(const QString& location) const;

    QList<QSharedPointer<LePlugin> > getPlugins() const;

    QList<QSharedPointer<LePlugin> > getActivePlugins() const;

    void startPlugins(const QList<LePlugin*>& slist) const;
};

#endif // LEPLUGINS_P_H
