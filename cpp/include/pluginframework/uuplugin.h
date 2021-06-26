#ifndef UUPLUGIN_H
#define UUPLUGIN_H
#include "uupluginfw_global.h"

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

    enum StartOption
    {
        START_TRANSIENT = 0x00000001,
        START_ACTIVATION_POLICY = 0x00000002
    };
    Q_DECLARE_FLAGS(StartOptions, StartOption)

    enum StopOption
    {
        STOP_TRANSIENT = 0x00000001
    };
    Q_DECLARE_FLAGS(StopOptions, StopOption)

    virtual ~uuPlugin();

    State getState() const;

    virtual void start(const StartOptions& options = START_ACTIVATION_POLICY);

    virtual void stop(const StopOptions& options = 0);

    void update(const QUrl &updateLocation = QUrl());

    virtual void uninstall();

    uuPluginContext* getPluginContext() const;

    long getPluginId() const;

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
Q_DECL_METATYPE(QSharedPointer<uuPlugin>)

Q_DECLARE_OPERATORS_FOR_FLAGS(uuPlugin::States)
Q_DECLARE_OPERATORS_FOR_FLAGS(uuPlugin::StartOptions)
Q_DECLARE_OPERATORS_FOR_FLAGS(uuPlugin::StopOptions)

#endif // UUPLUGIN_H
