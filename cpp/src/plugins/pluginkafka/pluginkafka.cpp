#include "stable.h"
#include "pluginkafka.h"

#include <QDebug>
#include <QtPlugin>

PluginKafka::PluginKafka()
{
}

void PluginKafka::start(uuPluginContext* context)
{
    context;
    qDebug() << "PluginFramework->PluginKafka[Start]";
}

void PluginKafka::stop(uuPluginContext* context)
{
    context;
    qDebug() << "PluginFramework->PluginKafka[Stop]";
}

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN2(plugin_kafka, PluginKafka)
#endif
