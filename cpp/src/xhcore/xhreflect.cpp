#include "stable.h"
#include "xhreflect.h"
#include <list>
#include <QDebug>

static std::list<xhReflect*> connRegistered;

void xh_registerReflect(xhReflect* reflect)
{
    qDebug() << "xhrelfect[register]: " << reflect->cid();
    connRegistered.push_back(reflect);
}

void xh_unregisterReflect(xhReflect* reflect)
{
    qDebug() << "xhrelfect[unregister]: " << reflect->cid();
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
