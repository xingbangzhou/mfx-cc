#include "stable.h"
#include "pluginaservice.h"

#include <QDebug>

PluginAService::PluginAService(XhPluginContext* pc)
{
	pc->registerService<TestAService>(this);
}

void PluginAService::callA()
{
	qDebug().nospace() << "I'm TestAService";
}
