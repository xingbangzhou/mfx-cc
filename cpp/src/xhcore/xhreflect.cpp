#include "stable.h"
#include "xhreflect.h"

#include <list>

static std::list<xhReflect*> connRegistered;

void registerXHReflect(xhReflect* reflect)
{
    connRegistered.push_back(reflect);
}

void unregisterXHReflect(xhReflect* reflect)
{
    connRegistered.remove(reflect);
}

QObject* createXHObject(const QString& iid)
{
    auto itr = std::find_if(
        connRegistered.begin(),
        connRegistered.end(), [&iid](xhReflect * &reflect) -> auto { return reflect->iid() == iid; });
    if (itr == connRegistered.end())
    {
        return nullptr;
    }
    return (*itr)->createObject();
}
