#ifndef LESERVICEREFERENCE_H
#define LESERVICEREFERENCE_H

#include <QVariant>

#include "lepluginfwexport.h"
#include "leplugin.h"

class LeServiceRegistrationPrivate;
class LeServiceReferencePrivate;

class LEPLUGINFW_EXPORT LeServiceReference
{
public:

    LeServiceReference();

    LeServiceReference(const LeServiceReference& ref);

    operator bool() const;

    LeServiceReference& operator=(int null);

    ~LeServiceReference();

    QSharedPointer<LePlugin> getPlugin() const;

    QList<QSharedPointer<LePlugin> > getUsingPlugins() const;

    bool operator<(const LeServiceReference& reference) const;

    bool operator==(const LeServiceReference& reference) const;

    LeServiceReference& operator=(const LeServiceReference& reference);

protected:
    friend class LeServiceRegistrationPrivate;

    friend uint LEPLUGINFW_EXPORT qHash(const LeServiceReference&);

    LeServiceReference(LeServiceRegistrationPrivate* reg);

    LeServiceReferencePrivate * d_ptr;

private:
  Q_DECLARE_PRIVATE(LeServiceReference)
};

uint LEPLUGINFW_EXPORT qHash(const LeServiceReference& srf);

Q_DECLARE_METATYPE(LeServiceReference)

#endif // LESERVICEREFERENCE_H
