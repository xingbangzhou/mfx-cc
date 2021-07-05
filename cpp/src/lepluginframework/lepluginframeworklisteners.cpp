#include "stable.h"
#include "lepluginframeworklisteners.h"
#include "lepluginframeworkcontext.h"

LePluginFrameworkListeners::LePluginFrameworkListeners(LePluginFrameworkContext* fwCtx)
    : m_fwCtx(fwCtx)
{

}

void LePluginFrameworkListeners::addServiceSlot(
        QSharedPointer<LePlugin> plugin, QObject *receiver,
        const char *slot)
{
    QMutexLocker lock(&m_mutex);
    LeServiceSlotEntry sse(plugin, receiver, slot);
    if (m_serviceSet.contains(sse))
    {
        removeServiceSlot_unlocked(plugin, receiver, slot);
    }
    m_serviceSet.insert(sse);

    connect(receiver, SIGNAL(destroyed(QObject*)), this, SLOT(serviceListenerDestroyed(QObject*)), Qt::DirectConnection);
}

void LePluginFrameworkListeners::removeServiceSlot(QSharedPointer<LePlugin> plugin,
                                                   QObject *receiver,
                                                   const char *slot)
{
    QMutexLocker lock(&m_mutex);
    removeServiceSlot_unlocked(plugin, receiver, slot);
}

QSet<LeServiceSlotEntry> LePluginFrameworkListeners::getMatchingServiceSlots(const LeServiceReference &sr)
{
	sr;
    QMutexLocker lock(&m_mutex);

    return m_serviceSet;
}

void LePluginFrameworkListeners::removeServiceSlot_unlocked(QSharedPointer<LePlugin> plugin,
                                                            QObject *receiver,
                                                            const char *slot)
{
    LeServiceSlotEntry entryToRemove(plugin, receiver, slot);
    QMutableSetIterator<LeServiceSlotEntry> it(m_serviceSet);
    while (it.hasNext())
    {
        LeServiceSlotEntry currentEntry = it.next();
        if (currentEntry == entryToRemove)
        {
            currentEntry.setRemoved(true);
            it.remove();
        }
    }

    if (plugin)
    {
        disconnect(receiver, SIGNAL(destroyed(QObject*)), this, SLOT(serviceListenerDestroyed(QObject*)));
    }
}

void LePluginFrameworkListeners::serviceChanged(
        const QSet<LeServiceSlotEntry> &receivers,
        const LeServiceEvent& evt)
{
    LeServiceReference sr = evt.getServiceReference();

    foreach(LeServiceSlotEntry sse, receivers)
    {
        sse.invokeSlot(evt);
    }
}

void LePluginFrameworkListeners::serviceListenerDestroyed(QObject* listener)
{
	this->removeServiceSlot(QSharedPointer<LePlugin>(nullptr), listener, 0);
}
