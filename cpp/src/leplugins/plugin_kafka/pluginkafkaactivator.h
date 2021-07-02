#ifndef PLUGINKAFKAACTIVATOR_H
#define PLUGINKAFKAACTIVATOR_H

#include <QObject>

#include "lepluginframework/lepluginactivator.h"

class PluginKafkaActivator : public QObject,
    public LePluginActivator
{
    Q_OBJECT
    Q_INTERFACES(uuPluginActivator)
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "plugin_kafka")
#endif
public:
    PluginKafkaActivator();
    
    void start(LePluginContext* context);
    void stop(LePluginContext* context);
    
};

#endif // PLUGINKAFKAACTIVATOR_H
