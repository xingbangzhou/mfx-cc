#ifndef LEPLUGINFRAMEWORKCONTEXT_H
#define LEPLUGINFRAMEWORKCONTEXT_H

#include "lepluginframework/lepluginframework.h"
#include "leplugins.h"

class LePluginPrivate;

class LePluginFrameworkContext
{
public:

    LePlugins* plugins;

    QSharedPointer<LePluginFramework> systemPlugin;

    LePluginFrameworkContext();
    ~LePluginFrameworkContext();

    void init();

    void uninit();

    void resolvePlugin(LePluginPrivate* plugin);

private:
    bool initialized;
};

#endif // LEPLUGINFRAMEWORKCONTEXT_H
