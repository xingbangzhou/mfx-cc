#include "stable.h"
#include "framework.h"
#include "xhpluginframework/xhplugincontext.h"

#include "shared/testaservice.h"

#include <QTimer>
#include <QCoreApplication>

FrameWork::FrameWork(QObject* parent)
    : QObject(parent), m_logger("FrameWork")
{
    m_pluginFw = m_fwFactory.getFramework();

	m_pluginFw->init();

    m_pluginFw->getPluginContext()->connectServiceListener(this, "onServiceListening");

}

QSharedPointer<XhPluginFramework> FrameWork::getPluginFw()
{
    return m_pluginFw;
}

void FrameWork::init()
{
    m_pluginFw->start();
}

void FrameWork::testService()
{
    QTimer::singleShot(1000, this, SLOT(onTestService()));
}

void FrameWork::onServiceListening(XhServiceEvent event)
{
    m_logger.info("OnServiceListening: type: " + event.getType());
    if (event.getType() == XhServiceEvent::REGISTERED)
    {
        TestAService* service = m_pluginFw->getPluginContext()->getService<TestAService>(event.getServiceReference());
        service->callA();
    }
}

void FrameWork::onTestService()
{
    QSharedPointer<XhPlugin> plugin = m_pluginFw->getPluginContext()->installPlugin(QUrl::fromLocalFile(qApp->applicationDirPath() + "/plugina_test.dll"));

    plugin->start();
}
