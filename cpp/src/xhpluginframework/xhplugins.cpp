#include "stable.h"
#include "xhplugins.h"
#include "xhpluginframeworkcontext.h"
#include "xhplugin_p.h"

XhPlugins::XhPlugins(XhPluginFrameworkContext* fw)
{
    fwCtx = fw;
    plugins.insert(fw->systemPlugin->getLocation(), fw->systemPlugin);
}

void XhPlugins::clear()
{
    QWriteLocker lock(&pluginsLock);
    plugins.clear();
    fwCtx = nullptr;
}

QSharedPointer<XhPlugin> XhPlugins::install(const QUrl &location)
{
    QSharedPointer<XhPlugin> res;
    QMutexLocker lock(&objectLock);

    QHash<QString, QSharedPointer<XhPlugin> >::const_iterator it = plugins.find(location.toString());
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

    res = QSharedPointer<XhPlugin>(new XhPlugin());
    res->init(res, fwCtx, localPluginPath);
    plugins.insert(location.toString(), res);
	
	fwCtx->logger().info(location.fileName() + ": install");

    return res;
}

void XhPlugins::remove(const QUrl &location)
{
    QWriteLocker lock(&pluginsLock);
    plugins.remove(location.toString());
}

QSharedPointer<XhPlugin> XhPlugins::getPlugin(const QString &location) const
{
    QReadLocker lock(&pluginsLock);
    QHash<QString, QSharedPointer<XhPlugin> >::const_iterator it = plugins.find(location);
    if (it == plugins.end()) return it.value();
    return QSharedPointer<XhPlugin>(nullptr);
}

QList<QSharedPointer<XhPlugin> > XhPlugins::getPlugins() const
{
    QReadLocker lock(&pluginsLock);
    return plugins.values();
}

QList<QSharedPointer<XhPlugin> > XhPlugins::getActivePlugins() const
{
    QList<QSharedPointer<XhPlugin> > slist;
    {
        QReadLocker lock(&pluginsLock);
        QHashIterator<QString, QSharedPointer<XhPlugin> > it(plugins);
        while (it.hasNext()) {
            QSharedPointer<XhPlugin> plugin = it.next().value();
            XhPlugin::State s = plugin->getState();
            if (s == XhPlugin::ACTIVE || s == XhPlugin::STARTING)
            {
                slist.push_back(plugin);
            }
        }
    }
    return slist;
}

void XhPlugins::startPlugins(const QList<XhPlugin*>& slist) const
{
	QListIterator<XhPlugin*> it(slist);
	while (it.hasNext())
	{
		XhPlugin* plugin = it.next();
		XhPluginPrivate* pp = plugin->d_func();
		pp->getUpdatedState();
	}

	it.toFront();
	while (it.hasNext())
	{
		XhPlugin* plugin = it.next();
		XhPluginPrivate* pp = plugin->d_func();
		if (pp->getUpdatedState() == XhPlugin::RESOLVED)
		{
			plugin->start();
		}
	}
}
