#ifndef UUPLUGIN_H
#define UUPLUGIN_H

#include <QMetaType>
#include <QUrl>
#include <QSharedPointer>
#include <QWeakPointer>

#include "uupluginfwexport.h"

class uuPluginContext;
class uuPluginFramework;
class uuPluginArchive;
class uuPluginPrivate;
class uuPluginFrameworkContext;

class UUPLUGINFW_EXPORT uuPlugin
{
public:
    // 插件状态
    enum State
    {
        UNINSTALLED = 0x00000001,
        INSTALLED = 0x00000002,
        RESOLVED = 0x00000004,
        STARTING = 0x00000008,
        STOPPING = 0x00000010,
        ACTIVE = 0x00000020
    };
    Q_DECLARE_FLAGS(States, State)

    virtual ~uuPlugin();

    State getState() const;

    virtual void start();

    virtual void stop();

    virtual void uninstall();

    uuPluginContext* getPluginContext() const;

    QString getLocation() const;

protected:
    friend class uuPluginPrivate;
    friend class uuPlugins;

    uuPluginPrivate* d_ptr;

    uuPlugin();
    void init(uuPluginPrivate* dd);
    void init(const QWeakPointer<uuPlugin>& self, uuPluginFrameworkContext* fw, const QString& loc);

private:
    Q_DECLARE_PRIVATE(uuPlugin)
    Q_DISABLE_COPY(uuPlugin)
};

Q_DECLARE_METATYPE(uuPlugin*)
Q_DECLARE_METATYPE(QSharedPointer<uuPlugin>)

Q_DECLARE_OPERATORS_FOR_FLAGS(uuPlugin::States)

#endif // UUPLUGIN_H
