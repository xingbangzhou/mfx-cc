#include "stable.h"
#include "leplugins.h"
#include "lepluginframeworkcontext.h"
#include "leplugin_p.h"

LePlugins::LePlugins(LePluginFrameworkContext* fw)
{
    fwCtx = fw;
    plugins.insert(fw->systemPlugin->getLocation(), fw->systemPlugin);
}

void LePlugins::clear()
{
    QWriteLocker lock(&pluginsLock);
    plugins.clear();
    fwCtx = nullptr;
}

QSharedPointer<LePlugin> LePlugins::install(const QUrl &location)
{
    QSharedPointer<LePlugin> res;
    QMutexLocker lock(&objectLock);

    QHash<QString, QSharedPointer<LePlugin> >::const_iterator it = plugins.find(location.toString());
    if (it != plugins.end())
    {
        return it.value();
    }

    QString localPluginPath;
	if (location.scheme() != "file")
    {
		fwCtx->logger().error(location.fileName() + ": scheme is no FILE");
        return nullptr;
    }
    else
    {
        localPluginPath = location.toLocalFile();
    }

    res = QSharedPointer<LePlugin>(new LePlugin());
    res->init(res, fwCtx, localPluginPath);
    plugins.insert(location.toString(), res);
	
	fwCtx->logger().info(location.fileName() + ": install");

    return res;
}

void LePlugins::remove(const QUrl &location)
{
    QWriteLocker lock(&pluginsLock);
    plugins.remove(location.toString());
}

QSharedPointer<LePlugin> LePlugins::getPlugin(const QString &location) const
{
    QReadLocker lock(&pluginsLock);
    QHash<QString, QSharedPointer<LePlugin> >::const_iterator it = plugins.find(location);
    if (it == plugins.end()) return it.value();
    return QSharedPointer<LePlugin>(nullptr);
}

QList<QSharedPointer<LePlugin> > LePlugins::getPlugins() const
{
    QReadLocker lock(&pluginsLock);
    return plugins.values();
}

QList<QSharedPointer<LePlugin> > LePlugins::getActivePlugins() const
{
    QList<QSharedPointer<LePlugin> > slist;
    {
        QReadLocker lock(&pluginsLock);
        QHashIterator<QString, QSharedPointer<LePlugin> > it(plugins);
        while (it.hasNext()) {
            QSharedPointer<LePlugin> plugin = it.next().value();
            LePlugin::State s = plugin->getState();
            if (s == LePlugin::ACTIVE || s == LePlugin::STARTING)
            {
                slist.push_back(plugin);
            }
        }
    }
    return slist;
}

void LePlugins::startPlugins(const QList<LePlugin*>& slist) const
{
	QListIterator<LePlugin*> it(slist);
	while (it.hasNext())
	{
		LePlugin* plugin = it.next();
		LePluginPrivate* pp = plugin->d_func();
		pp->getUpdatedState();
	}

	it.toFront();
	while (it.hasNext())
	{
		LePlugin* plugin = it.next();
		LePluginPrivate* pp = plugin->d_func();
		if (pp->getUpdatedState() == LePlugin::RESOLVED)
		{
			plugin->start();
		}
	}
}
