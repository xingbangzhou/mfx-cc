#ifndef LEPLUGINFRAMEWORKLISTENERS_H
#define LEPLUGINFRAMEWORKLISTENERS_H

#include <QObject>
#include <QSet>
#include <QMutex>

#include "lepluginframework/leserviceevent.h"
#include "lepluginframework/leservicereference.h"
#include "leserviceslotentry.h"

class LePluginFrameworkContext;

class LePluginFrameworkListeners : public QObject
{
    Q_OBJECT

public:

    explicit LePluginFrameworkListeners(LePluginFrameworkContext* fwCtx);

    void addServiceSlot(QSharedPointer<LePlugin> plugin, QObject* receiver,
                        const char* slot);

    void removeServiceSlot(QSharedPointer<LePlugin> plugin, QObject* receiver,
                           const char* slot);

    QSet<LeServiceSlotEntry> getMatchingServiceSlots(const LeServiceReference& sr);

    void serviceChanged(const QSet<LeServiceSlotEntry>& receivers, const LeServiceEvent& evt);

private slots:

    void serviceListenerDestroyed(QObject* listener);

private:

    QMutex m_mutex;

    LePluginFrameworkContext* m_fwCtx;

    QSet<LeServiceSlotEntry> m_serviceSet;

    void removeServiceSlot_unlocked(QSharedPointer<LePlugin> plugin, QObject* receiver,
                                    const char* slot);
};

#endif // LEPLUGINFRAMEWORKLISTENERS_H
