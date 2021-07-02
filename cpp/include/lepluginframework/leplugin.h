#ifndef LEPLUGIN_H
#define LEPLUGIN_H

#include <QMetaType>
#include <QUrl>
#include <QSharedPointer>
#include <QWeakPointer>

#include "lepluginfwexport.h"
#include "lecore/lelogger.h"

class LePluginContext;
class LePluginFramework;
class LePluginArchive;
class LePluginPrivate;
class LePluginFrameworkContext;

class LEPLUGINFW_EXPORT LePlugin
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

    virtual ~LePlugin();

    State getState() const;

    virtual void start();

    virtual void stop();

    virtual void uninstall();

    LePluginContext* getPluginContext() const;

    QString getLocation() const;

protected:
    friend class LePluginPrivate;
    friend class LePlugins;

    LePluginPrivate* d_ptr;

    LePlugin();
    void init(LePluginPrivate* dd);
    void init(const QWeakPointer<LePlugin>& self, LePluginFrameworkContext* fw, const QString& loc);

private:
    Q_DECLARE_PRIVATE(LePlugin)
    Q_DISABLE_COPY(LePlugin)
};

Q_DECLARE_METATYPE(LePlugin*)
Q_DECLARE_METATYPE(QSharedPointer<LePlugin>)

Q_DECLARE_OPERATORS_FOR_FLAGS(LePlugin::States)

#endif // LEPLUGIN_H
