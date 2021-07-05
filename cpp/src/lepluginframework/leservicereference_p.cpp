#include "stable.h"
#include "leservicereference_p.h"
#include "leserviceregistration_p.h"

LeServiceReferencePrivate::LeServiceReferencePrivate(LeServiceRegistrationPrivate* reg)
    : ref(1), registration(reg)
{
    if (registration)
    {
        registration->ref.ref();
    }
}

LeServiceReferencePrivate::~LeServiceReferencePrivate()
{
  if (registration && !registration->ref.deref())
  {
      delete registration;
  }
}

QObject* LeServiceReferencePrivate::getService(QSharedPointer<LePlugin> plugin)
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

bool LeServiceReferencePrivate::ungetService(QSharedPointer<LePlugin> plugin, bool checkRefCounter)
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
