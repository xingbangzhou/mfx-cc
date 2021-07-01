#ifndef UUPLUGINCONTEXT_H
#define UUPLUGINCONTEXT_H

#include <QSharedPointer>
#include <QIODevice>

#include "uupluginfwexport.h"

class uuPlugin;
class uuPluginPrivate;
class uuPluginFrameworkPrivate;
class uuPluginContextPrivate;

class UUPLUGINFW_EXPORT uuPluginContext
{
public:
    ~uuPluginContext();

    QSharedPointer<uuPlugin> getPlugin() const;

    QList<QSharedPointer<uuPlugin> > getPlugins() const;

    QSharedPointer<uuPlugin> installPlugin(const QUrl& location);

protected:
    friend class uuPlugin;
    friend class uuPluginPrivate;
    friend class uuPluginFrameworkPrivate;

    explicit uuPluginContext(uuPluginPrivate* plugin);

    uuPluginContextPrivate* const d_ptr;

private:
   Q_DECLARE_PRIVATE(uuPluginContext);
};

#endif // UUPLUGINCONTEXT_H
