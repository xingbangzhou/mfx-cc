#ifndef UUPLUGINCONTEXT_H
#define UUPLUGINCONTEXT_H

#include <QSharedPointer>
#include <QIODevice>

#include "uupluginfwexport.h"

class uuPlugin;
class uuPluginPrivate;
class uuPluginContextPrivate;
class uuPluginFrameworkPrivate;

class UUPLUGINFW_EXPORT uuPluginContext
{
public:
    ~uuPluginContext();

    QSharedPointer<uuPlugin> getPlugin() const;

    QList<QSharedPointer<uuPlugin> > getPlugins() const;

    QSharedPointer<uuPlugin> installPlugin(const QUrl& location, QIODevice* input = NULL);

protected:
    friend class uuPlugin;
    friend class uuPluginPrivate;
    friend class uuPluginFrameworkPrivate;

    explicit uuPluginContext(uuPluginPrivate* plugin);

    uuPluginContextPrivate * const d_ptr;

private:
    Q_DECLARE_PRIVATE(uuPluginContext)
};

#endif // UUPLUGINCONTEXT_H
