#include "stable.h"
#include "xhserviceslotentry.h"
#include "xhpluginframework/xhplugin.h"

#include <QSharedData>

class XhServiceSlotEntryData : public QSharedData
{
public:

    XhServiceSlotEntryData(QSharedPointer<XhPlugin> p, QObject* receiver, const char* slot)
        : plugin(p), receiver(receiver),
          slot(slot), removed(false), hashValue(0)
    {

    }

    QSharedPointer<XhPlugin> plugin;
    QObject* receiver;
    const char* slot;
    bool removed;

    uint hashValue;
};

//----------------------------------------------------------------------------
XhServiceSlotEntry::XhServiceSlotEntry(
        QSharedPointer<XhPlugin> p, QObject* receiver, const char* slot)
    : d(new XhServiceSlotEntryData(p, receiver, slot))
{

}

XhServiceSlotEntry::XhServiceSlotEntry(const XhServiceSlotEntry& other)
    : d(other.d)
{

}

XhServiceSlotEntry::XhServiceSlotEntry()
    : d(new XhServiceSlotEntryData(QSharedPointer<XhPlugin>(0), 0, 0))
{

}

XhServiceSlotEntry::~XhServiceSlotEntry()
{

}

XhServiceSlotEntry& XhServiceSlotEntry::operator=(const XhServiceSlotEntry &other)
{
    d = other.d;
    return *this;
}

bool XhServiceSlotEntry::operator==(const XhServiceSlotEntry& other) const
{
    return ((d->plugin == 0 || other.d->plugin == 0) || d->plugin == other.d->plugin) &&
            d->receiver == other.d->receiver &&
            ((d->slot == 0 || other.d->slot == 0) || std::strcmp(d->slot, other.d->slot) == 0);
}

void XhServiceSlotEntry::invokeSlot(const XhServiceEvent &event)
{
    if (!QMetaObject::invokeMethod(d->receiver, d->slot,
                                   Qt::DirectConnection,
                                   Q_ARG(XhServiceEvent, event)))
    {
		
    }
}

void XhServiceSlotEntry::setRemoved(bool removed)
{
    d->removed = removed;
}

bool XhServiceSlotEntry::isRemoved() const
{
    return d->removed;
}

QSharedPointer<XhPlugin> XhServiceSlotEntry::getPlugin() const
{
    return d->plugin;
}

uint qHash(const XhServiceSlotEntry& serviceSlot)
{
    if (serviceSlot.d->hashValue == 0)
    {
        serviceSlot.d->hashValue = qHash(serviceSlot.d->plugin) * 4 +
                qHash(serviceSlot.d->receiver) * 2 + qHash(QString(serviceSlot.d->slot));
    }
    return serviceSlot.d->hashValue;
}
