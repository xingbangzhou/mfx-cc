#ifndef UUPLUGIN_H
#define UUPLUGIN_H
#include "uupluginfwexport.h"

#include <QMetaType>
#include <QUrl>
#include <QSharedPointer>

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

    long getPluginId() const;

    QString getLocation() const;

    QString getSymbolicName() const;

protected:
    friend class uuPluginPrivate;

    uuPluginPrivate* d_ptr;

    explicit uuPlugin();
    void init(uuPluginPrivate* dd);
    void init(const QWeakPointer<uuPlugin>& self, uuPluginFrameworkContext* fw);

private:
    Q_DECLARE_PRIVATE(uuPlugin)
    Q_DISABLE_COPY(uuPlugin)
};

Q_DECL_METATYPE(uuPlugin*)
Q_DECLARE_METATYPE(QSharedPointer<uuPlugin>)

Q_DECLARE_OPERATORS_FOR_FLAGS(uuPlugin::States)
Q_DECLARE_OPERATORS_FOR_FLAGS(uuPlugin::StartOptions)
Q_DECLARE_OPERATORS_FOR_FLAGS(uuPlugin::StopOptions)

#endif // UUPLUGIN_H
