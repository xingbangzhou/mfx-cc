#ifndef XHSERVICEEVENT_H
#define XHSERVICEEVENT_H

#include <QSharedDataPointer>

#include "xhpluginframework/xhpluginfwexport.h"
#include "xhservicereference.h"

class XhServiceEventData;

class XHPLUGINFW_EXPORT XhServiceEvent
{
public:

    enum Type
    {
        REGISTERED = 0x00000001,
        MODIFIED = 0x00000002,
        UNREGISTERING = 0x00000004,
        MODIFIED_ENDMATCH = 0x00000008
    };

    XhServiceEvent();
    ~XhServiceEvent();

    bool isNull() const;

    XhServiceEvent(Type type, const XhServiceReference& reference);

    XhServiceEvent(const XhServiceEvent& other);

    XhServiceEvent& operator=(const XhServiceEvent& other);

    XhServiceReference getServiceReference() const;

    Type getType() const;

private:

    QSharedDataPointer<XhServiceEventData> d;
};

Q_DECLARE_METATYPE(XhServiceEvent)

#endif // XHSERVICEEVENT_H
