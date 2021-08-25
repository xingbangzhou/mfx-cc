#include "stable.h"
#include "xhpluginframeworklisteners.h"
#include "xhpluginframeworkcontext.h"

XhPluginFrameworkListeners::XhPluginFrameworkListeners(XhPluginFrameworkContext* fwCtx)
    : m_fwCtx(fwCtx)
{

}

void XhPluginFrameworkListeners::addServiceSlot(
        QSharedPointer<XhPlugin> plugin, QObject *receiver,
        const char *slot)
{
    QMutexLocker lock(&m_mutex);
    XhServiceSlotEntry sse(plugin, receiver, slot);
    if (m_serviceSet.contains(sse))
    {
        removeServiceSlot_unlocked(plugin, receiver, slot);
    }
    m_serviceSet.insert(sse);

    connect(receiver, SIGNAL(destroyed(QObject*)), this, SLOT(serviceListenerDestroyed(QObject*)), Qt::DirectConnection);
}

void XhPluginFrameworkListeners::removeServiceSlot(QSharedPointer<XhPlugin> plugin,
                                                   QObject *receiver,
                                                   const char *slot)
{
    QMutexLocker lock(&m_mutex);
    removeServiceSlot_unlocked(plugin, receiver, slot);
}

QSet<XhServiceSlotEntry> XhPluginFrameworkListeners::getMatchingServiceSlots(const XhServiceReference &sr)
{
	sr;
    QMutexLocker lock(&m_mutex);

    return m_serviceSet;
}

void XhPluginFrameworkListeners::removeServiceSlot_unlocked(QSharedPointer<XhPlugin> plugin,
                                                            QObject *receiver,
                                                            const char *slot)
{
    XhServiceSlotEntry entryToRemove(plugin, receiver, slot);
    QMutableSetIterator<XhServiceSlotEntry> it(m_serviceSet);
    while (it.hasNext())
    {
        XhServiceSlotEntry currentEntry = it.next();
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

void XhPluginFrameworkListeners::serviceChanged(
        const QSet<XhServiceSlotEntry> &receivers,
        const XhServiceEvent& evt)
{
    XhServiceReference sr = evt.getServiceReference();

    foreach(XhServiceSlotEntry sse, receivers)
    {
        sse.invokeSlot(evt);
    }
}

void XhPluginFrameworkListeners::serviceListenerDestroyed(QObject* listener)
{
	this->removeServiceSlot(QSharedPointer<XhPlugin>(nullptr), listener, 0);
}
