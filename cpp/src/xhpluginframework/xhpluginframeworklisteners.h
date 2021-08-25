#ifndef XHPLUGINFRAMEWORKLISTENERS_H
#define XHPLUGINFRAMEWORKLISTENERS_H

#include <QObject>
#include <QSet>
#include <QMutex>

#include "xhpluginframework/xhserviceevent.h"
#include "xhpluginframework/xhservicereference.h"
#include "xhserviceslotentry.h"

class XhPluginFrameworkContext;

class XhPluginFrameworkListeners : public QObject
{
    Q_OBJECT

public:

    explicit XhPluginFrameworkListeners(XhPluginFrameworkContext* fwCtx);

    void addServiceSlot(QSharedPointer<XhPlugin> plugin, QObject* receiver,
                        const char* slot);

    void removeServiceSlot(QSharedPointer<XhPlugin> plugin, QObject* receiver,
                           const char* slot);

    QSet<XhServiceSlotEntry> getMatchingServiceSlots(const XhServiceReference& sr);

    void serviceChanged(const QSet<XhServiceSlotEntry>& receivers, const XhServiceEvent& evt);

private slots:

    void serviceListenerDestroyed(QObject* listener);

private:

    QMutex m_mutex;

    XhPluginFrameworkContext* m_fwCtx;

    QSet<XhServiceSlotEntry> m_serviceSet;

    void removeServiceSlot_unlocked(QSharedPointer<XhPlugin> plugin, QObject* receiver,
                                    const char* slot);
};

#endif // XHPLUGINFRAMEWORKLISTENERS_H
