#ifndef XHSERVICESLOTENTRY_H
#define XHSERVICESLOTENTRY_H

#include <QString>
#include <QExplicitlySharedDataPointer>

#include "xhpluginframework/xhserviceevent.h"
#include "xhpluginframework/xhserviceevent.h"

class QObject;
class XhPlugin;
class XhServiceSlotEntryData;

class XhServiceSlotEntry
{
public:

    XhServiceSlotEntry(QSharedPointer<XhPlugin> p, QObject* receiver, const char* slot);

    XhServiceSlotEntry(const XhServiceSlotEntry& other);

    XhServiceSlotEntry();
    ~XhServiceSlotEntry();

    XhServiceSlotEntry& operator=(const XhServiceSlotEntry& other);

    bool operator==(const XhServiceSlotEntry& other) const;

    void invokeSlot(const XhServiceEvent& event);

    void setRemoved(bool removed);

    bool isRemoved() const;

    QSharedPointer<XhPlugin> getPlugin() const;

private:

    friend uint qHash(const XhServiceSlotEntry& serviceSlot);

    QExplicitlySharedDataPointer<XhServiceSlotEntryData> d;
};

uint qHash(const XhServiceSlotEntry& serviceSlot);

#endif // XHSERVICESLOTENTRY_H
