#ifndef PLUGINAACTIVATOR_H
#define PLUGINAACTIVATOR_H

#include <QObject>
#include <QScopedPointer>

#include "xhpluginframework/xhpluginactivator.h"
#include "pluginaservice.h"

class PluginAActivator : public QObject,
    public XhPluginActivator
{
    Q_OBJECT
    Q_INTERFACES(XhPluginActivator)
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "plugina_test")
#endif
public:
    PluginAActivator();
    
    void start(XhPluginContext* context);
    void stop(XhPluginContext* context);
    
private:
	QScopedPointer<PluginAService> m_service;
};

#endif // PLUGINAACTIVATOR_H
