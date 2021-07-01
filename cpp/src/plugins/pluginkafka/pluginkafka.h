#ifndef PLUGINKAFKA_H
#define PLUGINKAFKA_H

#include <QObject>

#include "pluginframework/uupluginactivator.h"

class PluginKafka : public QObject,
    public uuPluginActivator
{
    Q_OBJECT
    Q_INTERFACES(uuPluginActivator)
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "plugin_kafka")
#endif
public:
    PluginKafka();
    
    void start(uuPluginContext* context);
    void stop(uuPluginContext* context);
    
};

#endif // PLUGINKAFKA_H
