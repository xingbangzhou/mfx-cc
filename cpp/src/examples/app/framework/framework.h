#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <QSharedPointer>

#include "xhcore/xhlogger.h"
#include "xhpluginframework/xhpluginframeworkfactory.h"
#include "xhpluginframework/xhserviceevent.h"

class FrameWork : public QObject
{
    Q_OBJECT
public:
    explicit FrameWork(QObject* parent = nullptr);

    QSharedPointer<XhPluginFramework> getPluginFw();

    void init();

    void testService();

private slots:
    void onServiceListening(XhServiceEvent event);

    // test
    void onTestService();

private:
    XhPluginFrameworkFactory m_fwFactory;
    QSharedPointer<XhPluginFramework> m_pluginFw;

    XhLogger m_logger;
};

#endif // FRAMEWORK_H
