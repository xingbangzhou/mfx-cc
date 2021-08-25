#ifndef XHMAINFRAME_H
#define XHMAINFRAME_H

#include <QSharedPointer>

#include "xhcore/xhlogger.h"
#include "xhpluginframework/xhpluginframeworkfactory.h"
#include "xhpluginframework/xhserviceevent.h"

class XhMainFrame : public QObject
{
    Q_OBJECT
public:
    explicit XhMainFrame(QObject* parent = nullptr);

    QSharedPointer<XhPluginFramework> getPluginFw();

    void startFramework();

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

#endif // XHMAINFRAME_H
