#ifndef LESERVICESLOTENTRY_H
#define LESERVICESLOTENTRY_H

#include <QString>
#include <QExplicitlySharedDataPointer>

#include "lepluginframework/leserviceevent.h"
#include "lepluginframework/leserviceevent.h"

class QObject;
class LePlugin;
class LeServiceSlotEntryData;

class LeServiceSlotEntry
{
public:

    LeServiceSlotEntry(QSharedPointer<LePlugin> p, QObject* receiver, const char* slot);

    LeServiceSlotEntry(const LeServiceSlotEntry& other);

    LeServiceSlotEntry();
    ~LeServiceSlotEntry();

    LeServiceSlotEntry& operator=(const LeServiceSlotEntry& other);

    bool operator==(const LeServiceSlotEntry& other) const;

    void invokeSlot(const LeServiceEvent& event);

    void setRemoved(bool removed);

    bool isRemoved() const;

    QSharedPointer<LePlugin> getPlugin() const;

private:

    friend uint qHash(const LeServiceSlotEntry& serviceSlot);

    QExplicitlySharedDataPointer<LeServiceSlotEntryData> d;
};

uint qHash(const LeServiceSlotEntry& serviceSlot);

#endif // LESERVICESLOTENTRY_H
