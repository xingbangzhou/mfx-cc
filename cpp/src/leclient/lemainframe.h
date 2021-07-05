#ifndef LEMAINFRAME_H
#define LEMAINFRAME_H

#include <QSharedPointer>

#include "lecore/lelogger.h"
#include "lepluginframework/lepluginframeworkfactory.h"
#include "lepluginframework/leserviceevent.h"

class LeMainFrame : public QObject
{
    Q_OBJECT
public:
    explicit LeMainFrame(QObject* parent = nullptr);

    QSharedPointer<LePluginFramework> getPluginFw();

    void startFramework();

    void testService();

private slots:
    void onServiceListening(LeServiceEvent event);

    // test
    void onTestService();

private:
    LePluginFrameworkFactory m_fwFactory;
    QSharedPointer<LePluginFramework> m_pluginFw;

    LeLogger m_logger;
};

#endif // LEMAINFRAME_H
