#include "stable.h"
#include "leserviceslotentry.h"
#include "lepluginframework/leplugin.h"

#include <QSharedData>

class LeServiceSlotEntryData : public QSharedData
{
public:

    LeServiceSlotEntryData(QSharedPointer<LePlugin> p, QObject* receiver, const char* slot)
        : plugin(p), receiver(receiver),
          slot(slot), removed(false), hashValue(0)
    {

    }

    QSharedPointer<LePlugin> plugin;
    QObject* receiver;
    const char* slot;
    bool removed;

    uint hashValue;
};

//----------------------------------------------------------------------------
LeServiceSlotEntry::LeServiceSlotEntry(
        QSharedPointer<LePlugin> p, QObject* receiver, const char* slot)
    : d(new LeServiceSlotEntryData(p, receiver, slot))
{

}

LeServiceSlotEntry::LeServiceSlotEntry(const LeServiceSlotEntry& other)
    : d(other.d)
{

}

LeServiceSlotEntry::LeServiceSlotEntry()
    : d(new LeServiceSlotEntryData(QSharedPointer<LePlugin>(0), 0, 0))
{

}

LeServiceSlotEntry::~LeServiceSlotEntry()
{

}

LeServiceSlotEntry& LeServiceSlotEntry::operator=(const LeServiceSlotEntry &other)
{
    d = other.d;
    return *this;
}

bool LeServiceSlotEntry::operator==(const LeServiceSlotEntry& other) const
{
    return ((d->plugin == 0 || other.d->plugin == 0) || d->plugin == other.d->plugin) &&
            d->receiver == other.d->receiver &&
            ((d->slot == 0 || other.d->slot == 0) || std::strcmp(d->slot, other.d->slot) == 0);
}

void LeServiceSlotEntry::invokeSlot(const LeServiceEvent &event)
{
    if (!QMetaObject::invokeMethod(d->receiver, d->slot,
                                   Qt::DirectConnection,
                                   Q_ARG(LeServiceEvent, event)))
    {

    }
}

void LeServiceSlotEntry::setRemoved(bool removed)
{
    d->removed = removed;
}

bool LeServiceSlotEntry::isRemoved() const
{
    return d->removed;
}

QSharedPointer<LePlugin> LeServiceSlotEntry::getPlugin() const
{
    return d->plugin;
}

uint qHash(const LeServiceSlotEntry& serviceSlot)
{
    if (serviceSlot.d->hashValue == 0)
    {
        serviceSlot.d->hashValue = qHash(serviceSlot.d->plugin) * 4 +
                qHash(serviceSlot.d->receiver) * 2 + qHash(QString(serviceSlot.d->slot));
    }
    return serviceSlot.d->hashValue;
}
