#include "stable.h"
#include "framework.h"
#include "xhpluginframework/xhplugincontext.h"

#include "shared/testaservice.h"

#include <QTimer>
#include <QCoreApplication>
#include <QDebug>

FrameWork::FrameWork(QObject* parent)
    : QObject(parent)
    , m_logger("FrameWork")
    , library("plugina_test")
{
    m_pluginFw = m_fwFactory.getFramework();

	m_pluginFw->init();

    m_pluginFw->getPluginContext()->connectServiceListener(this, "onServiceListening");

    QObject::connect(this, SIGNAL(testSig(St, St)), this, SLOT(onTestSig(St, St)));
    QObject::connect(this, SIGNAL(testSig(St)), this, SLOT(onTestSig(St)));
    emit testSig(St(), St());
}

QSharedPointer<XhPluginFramework> FrameWork::getPluginFw()
{
    return m_pluginFw;
}

void FrameWork::init()
{
    m_pluginFw->start();
}


void FrameWork::testLoad()
{
    qDebug().nospace() << "testLoad:" << library.load();
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
    //QSharedPointer<XhPlugin> plugin = m_pluginFw->getPluginContext()->installPlugin(QUrl::fromLocalFile(qApp->applicationDirPath() + "/plugina_test.dll"));

    //plugin->start();

    //QTimer::singleShot(1000, [plugin]() -> void {
    //    plugin->uninstall();
    //});

    using Ptr = void* (*)();

    typedef struct
    {
        int x;
    } * pdata;

    auto ptr = (Ptr)library.resolve("printA");
    pdata sss = static_cast<pdata>(ptr());
    library.unload();
    sss->x = 12;
    qDebug() << sss->x << "-----------------------------------";
}

void FrameWork::onTestSig(St, St)
{
    qDebug() << "onTestSig-------------------------------";
}
