#include "stable.h"
#include "pluginkafkaactivator.h"

#include <QDebug>
#include <QtPlugin>

PluginKafkaActivator::PluginKafkaActivator()
{
}

void PluginKafkaActivator::start(LePluginContext* context)
{
    context;
    qDebug() << "PluginFramework->PluginKafka[Start]";
}

void PluginKafkaActivator::stop(LePluginContext* context)
{
    context;
    qDebug() << "PluginFramework->PluginKafka[Stop]";
}

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN2(plugin_kafka, PluginKafka)
#endif
