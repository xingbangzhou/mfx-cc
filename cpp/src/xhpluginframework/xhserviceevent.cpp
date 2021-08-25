#include "stable.h"
#include "xhpluginframework/xhserviceevent.h"

class XhServiceEventData : public QSharedData
{
public:

    XhServiceEventData(XhServiceEvent::Type type, const XhServiceReference& reference)
        : type(type), reference(reference)
    {

    }

    const XhServiceEvent::Type type;
    const XhServiceReference reference;
};

//----------------------------------------------------------------------------
XhServiceEvent::XhServiceEvent()
    : d(nullptr)
{

}

XhServiceEvent::~XhServiceEvent()
{

}

bool XhServiceEvent::isNull() const
{
    return !d;
}

XhServiceEvent::XhServiceEvent(Type type, const XhServiceReference& reference)
    : d(new XhServiceEventData(type, reference))
{

}

XhServiceEvent::XhServiceEvent(const XhServiceEvent& other)
    : d(other.d)
{

}

XhServiceEvent& XhServiceEvent::operator=(const XhServiceEvent& other)
{
    d = other.d;
    return *this;
}

XhServiceReference XhServiceEvent::getServiceReference() const
{
    return d->reference;
}

XhServiceEvent::Type XhServiceEvent::getType() const
{
  return d->type;
}
