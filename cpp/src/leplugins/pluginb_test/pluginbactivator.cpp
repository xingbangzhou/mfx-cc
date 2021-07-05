#include "stable.h"
#include "pluginbactivator.h"

#include <QDebug>
#include <QtPlugin>

PluginBActivator::PluginBActivator()
{
}

void PluginBActivator::start(LePluginContext* context)
{
    context;
    qDebug() << "PluginFramework->PluginKafka[Start]";
}

void PluginBActivator::stop(LePluginContext* context)
{
    context;
    qDebug() << "PluginFramework->PluginKafka[Stop]";
}

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN2(pluginb_test, PluginBActivator)
#endif
