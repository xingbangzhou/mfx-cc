#include "stable.h"
#include "lepluginframework/leserviceevent.h"

class LeServiceEventData : public QSharedData
{
public:

    LeServiceEventData(LeServiceEvent::Type type, const LeServiceReference& reference)
        : type(type), reference(reference)
    {

    }

    const LeServiceEvent::Type type;
    const LeServiceReference reference;
};

//----------------------------------------------------------------------------
LeServiceEvent::LeServiceEvent()
    : d(NULL)
{

}

LeServiceEvent::~LeServiceEvent()
{

}

bool LeServiceEvent::isNull() const
{
    return !d;
}

LeServiceEvent::LeServiceEvent(Type type, const LeServiceReference& reference)
    : d(new LeServiceEventData(type, reference))
{

}

LeServiceEvent::LeServiceEvent(const LeServiceEvent& other)
    : d(other.d)
{

}

LeServiceEvent& LeServiceEvent::operator=(const LeServiceEvent& other)
{
    d = other.d;
    return *this;
}

LeServiceReference LeServiceEvent::getServiceReference() const
{
    return d->reference;
}

LeServiceEvent::Type LeServiceEvent::getType() const
{
  return d->type;
}
