#ifndef XHPLUGINFRAMEWORKPRIVATE_H
#define XHPLUGINFRAMEWORKPRIVATE_H

#include "xhplugin_p.h"
#include "xhpluginframework/xhpluginframework.h"

class XhPluginFrameworkPrivate : public XhPluginPrivate
{
public:

    LockObject lock;

    XhPluginFrameworkPrivate(QWeakPointer<XhPlugin> qq, XhPluginFrameworkContext* fw);

    void init();

    void initSystemPlugin();

    void uninitSystemPlugin();

    void activate(XhPluginContext* context);
    void deactivate(XhPluginContext* context);

    void shutdown();

private:

    void shutdown0(bool wasActive);

    void stopAllPlugins();
};

#endif // XHPLUGINFRAMEWORKPRIVATE_H
