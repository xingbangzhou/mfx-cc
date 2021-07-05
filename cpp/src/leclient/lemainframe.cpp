#include "stable.h"
#include "lemainframe.h"
#include "lepluginframework/leplugincontext.h"

#include "shared/testaservice.h"

#include <QTimer>
#include <QCoreApplication>

LeMainFrame::LeMainFrame(QObject* parent)
    : QObject(parent), m_logger("LeMainFrame")
{
    m_pluginFw = m_fwFactory.getFramework();

	m_pluginFw->init();

    m_pluginFw->getPluginContext()->connectServiceListener(this, "onServiceListening");

}

QSharedPointer<LePluginFramework> LeMainFrame::getPluginFw()
{
    return m_pluginFw;
}

void LeMainFrame::startFramework()
{
    m_pluginFw->start();
}

void LeMainFrame::testService()
{
    QTimer::singleShot(1000, this, SLOT(onTestService()));
}

void LeMainFrame::onServiceListening(LeServiceEvent event)
{
    m_logger.info("OnServiceListening: type: " + event.getType());
    if (event.getType() == LeServiceEvent::REGISTERED)
    {
        TestAService* service = m_pluginFw->getPluginContext()->getService<TestAService>(event.getServiceReference());
        service->callA();
    }
}

void LeMainFrame::onTestService()
{
    QSharedPointer<LePlugin> plugin = m_pluginFw->getPluginContext()->installPlugin(QUrl::fromLocalFile(qApp->applicationDirPath() + "/plugina_test.dll"));

    plugin->start();
}
