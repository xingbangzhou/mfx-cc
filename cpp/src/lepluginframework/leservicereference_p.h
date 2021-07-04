#ifndef LESERVICEREFERENCEPRIVATE_H
#define LESERVICEREFERENCEPRIVATE_H

#include <QSharedPointer>
#include <QAtomicInt>

class QObject;
class LeServiceRegistrationPrivate;
class LePlugin;

class LeServiceReferencePrivate
{
public:
    LeServiceReferencePrivate(LeServiceRegistrationPrivate* reg);

    ~LeServiceReferencePrivate();

    QObject* getService(QSharedPointer<LePlugin> plugin);

    bool ungetService(QSharedPointer<LePlugin> plugin, bool checkRefCounter);

    QAtomicInt ref;

    LeServiceRegistrationPrivate* const registration;

private:

    Q_DISABLE_COPY(LeServiceReferencePrivate)
};

#endif // LESERVICEREFERENCEPRIVATE_H
