#ifndef PLUGINAACTIVATOR_H
#define PLUGINAACTIVATOR_H

#include <QObject>
#include <QScopedPointer>

#include "lepluginframework/lepluginactivator.h"
#include "pluginaservice.h"

class PluginAActivator : public QObject,
    public LePluginActivator
{
    Q_OBJECT
    Q_INTERFACES(LePluginActivator)
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "plugina_test")
#endif
public:
    PluginAActivator();
    
    void start(LePluginContext* context);
    void stop(LePluginContext* context);
    
private:
	QScopedPointer<PluginAService> m_service;
};

#endif // PLUGINAACTIVATOR_H
