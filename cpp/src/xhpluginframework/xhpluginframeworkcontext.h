#ifndef XHPLUGINFRAMEWORKCONTEXT_H
#define XHPLUGINFRAMEWORKCONTEXT_H

#include "xhpluginframework/xhpluginframework.h"
#include "xhplugins.h"
#include "xhpluginframeworklisteners.h"

class XhPluginPrivate;
class XhServices;

class XhPluginFrameworkContext
{
public:

    XhPlugins* plugins;

    XhPluginFrameworkListeners listeners;

    XhServices* services;

    QSharedPointer<XhPluginFramework> systemPlugin;

    XhPluginFrameworkContext();
    ~XhPluginFrameworkContext();

    void init();

    void uninit();

    void resolvePlugin(XhPluginPrivate* plugin);

	XhLogger& logger();

private:
    bool m_initialized;
	XhLogger m_logger;
};

#endif // XHPLUGINFRAMEWORKCONTEXT_H
