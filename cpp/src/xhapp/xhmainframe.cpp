#include "stable.h"
#include "xhmainframe.h"
#include "xhpluginframework/xhplugincontext.h"

#include "shared/testaservice.h"

#include <QTimer>
#include <QCoreApplication>

XhMainFrame::XhMainFrame(QObject* parent)
    : QObject(parent), m_logger("XhMainFrame")
{
    m_pluginFw = m_fwFactory.getFramework();

	m_pluginFw->init();

    m_pluginFw->getPluginContext()->connectServiceListener(this, "onServiceListening");

}

QSharedPointer<XhPluginFramework> XhMainFrame::getPluginFw()
{
    return m_pluginFw;
}

void XhMainFrame::startFramework()
{
    m_pluginFw->start();
}

void XhMainFrame::testService()
{
    QTimer::singleShot(1000, this, SLOT(onTestService()));
}

void XhMainFrame::onServiceListening(XhServiceEvent event)
{
    m_logger.info("OnServiceListening: type: " + event.getType());
    if (event.getType() == XhServiceEvent::REGISTERED)
    {
        TestAService* service = m_pluginFw->getPluginContext()->getService<TestAService>(event.getServiceReference());
        service->callA();
    }
}

void XhMainFrame::onTestService()
{
    QSharedPointer<XhPlugin> plugin = m_pluginFw->getPluginContext()->installPlugin(QUrl::fromLocalFile(qApp->applicationDirPath() + "/plugina_test.dll"));

    plugin->start();
}
