#include "stable.h"
#include "uuplugins_p.h"
#include "uupluginframeworkcontext_p.h"

uuPlugins::uuPlugins(uuPluginFrameworkContext* fw)
{
    fwCtx = fw;
    plugins.insert(fw->systemPlugin->getLocation(), fw->systemPlugin);
}

void uuPlugins::clear()
{
    QWriteLocker lock(&pluginsLock);
    plugins.clear();
    fwCtx = NULL;
}

QSharedPointer<uuPlugin> uuPlugins::install(const QUrl &location)
{
    QSharedPointer<uuPlugin> res;
    QMutexLocker lock(&objectLock);

    QHash<QString, QSharedPointer<uuPlugin> >::const_iterator it = plugins.find(location.toString());
    if (it != plugins.end())
    {
        return it.value();
    }

    QString localPluginPath;
    if (location.scheme() != "file")
    {
        // throw ctkRuntimeException(QString("Unsupported url scheme: ") + location.scheme());
        return NULL;
    }
    else
    {
        localPluginPath = location.toLocalFile();
    }

    res = QSharedPointer<uuPlugin>(new uuPlugin());
    res->init(res, fwCtx, location.toString());
    plugins.insert(location.toString(), res);

    // fwCtx->listeners.emitPluginChanged(ctkPluginEvent(ctkPluginEvent::INSTALLED, res));
    return res;
}

void uuPlugins::remove(const QUrl &location)
{
    QWriteLocker lock(&pluginsLock);
    plugins.remove(location.toString());
}

QSharedPointer<uuPlugin> uuPlugins::getPlugin(const QString &location) const
{
    QReadLocker lock(&pluginsLock);
    QHash<QString, QSharedPointer<uuPlugin> >::const_iterator it = plugins.find(location);
    if (it == plugins.end()) return it.value();
    return QSharedPointer<uuPlugin>(NULL);
}

QList<QSharedPointer<uuPlugin> > uuPlugins::getPlugins() const
{
    QReadLocker lock(&pluginsLock);
    return plugins.values();
}

QList<QSharedPointer<uuPlugin> > uuPlugins::getActivePlugins() const
{
    QList<QSharedPointer<uuPlugin> > slist;
    {
        QReadLocker lock(&pluginsLock);
        QHashIterator<QString, QSharedPointer<uuPlugin> > it(plugins);
        while (it.hasNext()) {
            QSharedPointer<uuPlugin> plugin = it.next().value();
            uuPlugin::State s = plugin->getState();
            if (s == uuPlugin::ACTIVE || s == uuPlugin::STARTING)
            {
                slist.push_back(plugin);
            }
        }
    }
    return slist;
}
