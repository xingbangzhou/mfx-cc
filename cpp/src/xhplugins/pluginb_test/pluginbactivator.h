#ifndef PLUGINBACTIVATOR_H
#define PLUGINBACTIVATOR_H

#include <QObject>

#include "xhpluginframework/xhpluginactivator.h"

class PluginBActivator : public QObject,
    public XhPluginActivator
{
    Q_OBJECT
    Q_INTERFACES(XhPluginActivator)
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "pluginb_test")
#endif
public:
	PluginBActivator();
    
    void start(XhPluginContext* context);
    void stop(XhPluginContext* context);
    
};

#endif // PLUGINBACTIVATOR_H
