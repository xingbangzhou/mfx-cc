#ifndef PLUGINBACTIVATOR_H
#define PLUGINBACTIVATOR_H

#include <QObject>

#include "lepluginframework/lepluginactivator.h"

class PluginBActivator : public QObject,
    public LePluginActivator
{
    Q_OBJECT
    Q_INTERFACES(LePluginActivator)
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "pluginb_test")
#endif
public:
	PluginBActivator();
    
    void start(LePluginContext* context);
    void stop(LePluginContext* context);
    
};

#endif // PLUGINBACTIVATOR_H
