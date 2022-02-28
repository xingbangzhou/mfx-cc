#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <QSharedPointer>
#include <QLibrary>

#include "xhcore/xhlogger.h"
#include "xhpluginframework/xhpluginframeworkfactory.h"
#include "xhpluginframework/xhserviceevent.h"

struct St
{

};

class FrameWork : public QObject
{
    Q_OBJECT
public:
    explicit FrameWork(QObject* parent = nullptr);

    QSharedPointer<XhPluginFramework> getPluginFw();

    void init();

    void testLoad();

signals:
    void testSig(St, St);
    void testSig(St);

private slots:
    void onServiceListening(XhServiceEvent event);

    // test
    void onTestService();

    void onTestSig(St, St);

private:
    XhPluginFrameworkFactory m_fwFactory;
    QSharedPointer<XhPluginFramework> m_pluginFw;

    XhLogger m_logger;

    QLibrary library;
};

#endif // FRAMEWORK_H
