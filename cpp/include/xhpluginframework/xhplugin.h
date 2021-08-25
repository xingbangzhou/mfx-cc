#ifndef XHPLUGIN_H
#define XHPLUGIN_H

#include <QMetaType>
#include <QUrl>
#include <QSharedPointer>
#include <QWeakPointer>

#include "xhpluginfwexport.h"
#include "xhcore/xhlogger.h"

class XhPluginContext;
class XhPluginFramework;
class XhPluginArchive;
class XhPluginPrivate;
class XhPluginFrameworkContext;

class XHPLUGINFW_EXPORT XhPlugin
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

    virtual ~XhPlugin();

    State getState() const;

    virtual void start();

    virtual void stop();

    virtual void uninstall();

    XhPluginContext* getPluginContext() const;

    QString getLocation() const;

protected:
    friend class XhPluginPrivate;
    friend class XhPlugins;

    XhPluginPrivate* d_ptr;

    XhPlugin();
    void init(XhPluginPrivate* dd);
    void init(const QWeakPointer<XhPlugin>& self, XhPluginFrameworkContext* fw, const QString& loc);

private:
    Q_DECLARE_PRIVATE(XhPlugin)
    Q_DISABLE_COPY(XhPlugin)
};

Q_DECLARE_METATYPE(XhPlugin*)
Q_DECLARE_METATYPE(QSharedPointer<XhPlugin>)

Q_DECLARE_OPERATORS_FOR_FLAGS(XhPlugin::States)

#endif // XHPLUGIN_H
