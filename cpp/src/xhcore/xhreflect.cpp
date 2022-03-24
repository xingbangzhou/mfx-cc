#include "stable.h"
#include "xhreflect.h"

#include <list>

static std::list<xhReflect*> connRegistered;

void xh_registerReflect(xhReflect* reflect)
{
    connRegistered.push_back(reflect);
}

void xh_unregisterReflect(xhReflect* reflect)
{
    connRegistered.remove(reflect);
}

QObject* xh_createObject(const QString& cid)
{
    auto itr = std::find_if(
        connRegistered.begin(),
        connRegistered.end(), [&cid](xhReflect * &reflect) -> auto { return reflect->cid() == cid; });
    if (itr == connRegistered.end())
    {
        return nullptr;
    }
    return (*itr)->createObject();
}
