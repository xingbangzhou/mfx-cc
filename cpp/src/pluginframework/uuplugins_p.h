#ifndef UUPLUGINS_P_H
#define UUPLUGINS_P_H

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

    void checkIllegalState() const;

public:
    uuPlugins(uuPluginFrameworkContext* fw);

    void clear();

    QSharedPointer<uuPlugin> install(const QUrl& location, QIODevice* in);

    void remove(const QUrl& location);

    QSharedPointer<uuPlugin> getPlugin(int id) const;

    QSharedPointer<uuPlugin> getPlugin(const QString& location) const;

     QList<QSharedPointer<uuPlugin> > getPlugins() const;

     QList<QSharedPointer<uuPlugin> > getActivePlugins() const;

     void load();

     void startPlugins(const QList<uuPlugin*>& slist) const;
};

#endif // UUPLUGINS_P_H
