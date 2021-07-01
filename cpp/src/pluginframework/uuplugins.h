#ifndef UUPLUGINS_H
#define UUPLUGINS_H

#include <QUrl>
#include <QHash>
#include <QSharedPointer>
#include <QReadWriteLock>
#include <QMutex>
#include <QIODevice>

#include "pluginframework/uuplugin.h"

class uuPluginFrameworkContext;

class uuPlugins
{
private:

    QHash<QString, QSharedPointer<uuPlugin> > plugins;

    uuPluginFrameworkContext* fwCtx;

    mutable QReadWriteLock pluginsLock;

    QMutex objectLock;

public:
    explicit uuPlugins(uuPluginFrameworkContext* fw);

    void clear();

    QSharedPointer<uuPlugin> install(const QUrl& location);

    void remove(const QUrl& location);

    QSharedPointer<uuPlugin> getPlugin(const QString& location) const;

    QList<QSharedPointer<uuPlugin> > getPlugins() const;

    QList<QSharedPointer<uuPlugin> > getActivePlugins() const;

    void startPlugins(const QList<uuPlugin*>& slist) const;
};

#endif // UUPLUGINS_P_H
