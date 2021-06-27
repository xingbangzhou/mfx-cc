#ifndef UUPLUGINCONTEXT_H
#define UUPLUGINCONTEXT_H
#include <QSharedPointer>

#include "uupluginfwexport.h"

class uuPlugin;
class uuPluginPrivate;
class uuPluginContextPrivate;

class UUPLUGINFW_EXPORT uuPluginContext
{
public:
    ~uuPluginContext();

    QSharedPointer<uuPlugin> getPlugin() const;

    QSharedPointer<uuPlugin> getPlugin(long id) const;

    QList<QSharedPointer<uuPlugin> > getPlugins() const;

protected:
    friend class uuPlugin;
    friend class uuPluginPrivate;

    explicit uuPluginContext(uuPluginPrivate* plugin);

    uuPluginContextPrivate * const d_ptr;

private:
    Q_DECLARE_PRIVATE(uuPluginContext)
};

#endif // UUPLUGINCONTEXT_H
