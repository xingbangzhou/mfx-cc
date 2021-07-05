#include "stable.h"
#include "pluginaactivator.h"

#include <QDebug>
#include <QtPlugin>

PluginAActivator::PluginAActivator()
{
}

void PluginAActivator::start(LePluginContext* context)
{
	m_service.reset(new PluginAService(context));
}

void PluginAActivator::stop(LePluginContext* context)
{
	Q_UNUSED(context);
}

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN2(plugina_test, PluginAActivator)
#endif
