#include "stable.h"
#include "pluginaactivator.h"

#include <QDebug>
#include <QtPlugin>

struct Struct0
{
    int x;
    Struct0(int _x = 1) : x(_x)
    {
        
    }   
    ~Struct0()
    {
        qDebug().nospace() << "~Struct0------------------" << x;
    }
};

Struct0 st0;
Struct0* pst = new Struct0(2);

void * printA()
{
    qDebug().nospace() << "printA()----------------------";
    return static_cast<void*>(pst);
}

PluginAActivator::PluginAActivator()
{
   
}

 PluginAActivator::~PluginAActivator()
{
}

void PluginAActivator::start(XhPluginContext* context)
{
	m_service.reset(new PluginAService(context));
}

void PluginAActivator::stop(XhPluginContext* context)
{
	Q_UNUSED(context);
    qDebug().nospace() << "TestAService stop";
}

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN2(plugina_test, PluginAActivator)
#endif
