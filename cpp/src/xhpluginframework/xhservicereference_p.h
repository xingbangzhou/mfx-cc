#ifndef XHSERVICEREFERENCEPRIVATE_H
#define XHSERVICEREFERENCEPRIVATE_H

#include <QSharedPointer>
#include <QAtomicInt>

class QObject;
class XhServiceRegistrationPrivate;
class XhPlugin;

class XhServiceReferencePrivate
{
public:
    XhServiceReferencePrivate(XhServiceRegistrationPrivate* reg);

    ~XhServiceReferencePrivate();

    QObject* getService(QSharedPointer<XhPlugin> plugin);

    bool ungetService(QSharedPointer<XhPlugin> plugin, bool checkRefCounter);

    QAtomicInt ref;

    XhServiceRegistrationPrivate* const registration;

private:

    Q_DISABLE_COPY(XhServiceReferencePrivate)
};

#endif // XHSERVICEREFERENCEPRIVATE_H
