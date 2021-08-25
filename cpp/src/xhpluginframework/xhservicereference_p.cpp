#include "stable.h"
#include "xhservicereference_p.h"
#include "xhserviceregistration_p.h"

XhServiceReferencePrivate::XhServiceReferencePrivate(XhServiceRegistrationPrivate* reg)
    : ref(1), registration(reg)
{
    if (registration)
    {
        registration->ref.ref();
    }
}

XhServiceReferencePrivate::~XhServiceReferencePrivate()
{
  if (registration && !registration->ref.deref())
  {
      delete registration;
  }
}

QObject* XhServiceReferencePrivate::getService(QSharedPointer<XhPlugin> plugin)
{
    QObject* s = nullptr;
    {
        QMutexLocker lock(&registration->propsLock);
        if (registration->available)
        {
            int count = registration->dependents.value(plugin);
            if (count == 0)
            {
                registration->dependents[plugin] = 1;
            }
            else
            {
                registration->dependents.insert(plugin, count + 1);
            }
            s = registration->getService();
        }
    }

    return s;
}

bool XhServiceReferencePrivate::ungetService(QSharedPointer<XhPlugin> plugin, bool checkRefCounter)
{
    QMutexLocker lock(&registration->propsLock);
    bool hasReferences = false;
    bool removeService = false;

    int count= registration->dependents.value(plugin);
    if (count > 0)
    {
        hasReferences = true;
    }

    if (checkRefCounter)
    {
        if (count > 1)
        {
            registration->dependents[plugin] = count - 1;
        }
        else if (count == 1)
        {
            removeService = true;
        }
    }
    else
    {
        removeService = true;
    }

    if (removeService)
    {
        registration->dependents.remove(plugin);
    }

    return hasReferences;
}
