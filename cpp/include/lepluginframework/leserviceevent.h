#ifndef LESERVICEEVENT_H
#define LESERVICEEVENT_H

#include <QSharedDataPointer>

#include "leservicereference.h"

class LeServiceEventData;

class LeServiceEvent
{
public:

    enum Type
    {
        REGISTERED = 0x00000001,
        MODIFIED = 0x00000002,
        UNREGISTERING = 0x00000004,
        MODIFIED_ENDMATCH = 0x00000008
    };

    LeServiceEvent();
    ~LeServiceEvent();

    bool isNull() const;

    LeServiceEvent(Type type, const LeServiceReference& reference);

    LeServiceEvent(const LeServiceEvent& other);

    LeServiceEvent& operator=(const LeServiceEvent& other);

    LeServiceReference getServiceReference() const;

    Type getType() const;

private:

    QSharedDataPointer<LeServiceEventData> d;
};

Q_DECLARE_METATYPE(LeServiceEvent)

#endif // LESERVICEEVENT_H
