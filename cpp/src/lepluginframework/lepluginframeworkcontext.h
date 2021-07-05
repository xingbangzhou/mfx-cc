#ifndef LEPLUGINFRAMEWORKCONTEXT_H
#define LEPLUGINFRAMEWORKCONTEXT_H

#include "lepluginframework/lepluginframework.h"
#include "leplugins.h"
#include "lepluginframeworklisteners.h"

class LePluginPrivate;
class LeServices;

class LePluginFrameworkContext
{
public:

    LePlugins* plugins;

    LePluginFrameworkListeners listeners;

    LeServices* services;

    QSharedPointer<LePluginFramework> systemPlugin;

    LePluginFrameworkContext();
    ~LePluginFrameworkContext();

    void init();

    void uninit();

    void resolvePlugin(LePluginPrivate* plugin);

	LeLogger& logger();

private:
    bool m_initialized;
	LeLogger m_logger;
};

#endif // LEPLUGINFRAMEWORKCONTEXT_H
