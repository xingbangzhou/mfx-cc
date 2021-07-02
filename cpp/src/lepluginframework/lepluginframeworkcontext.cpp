#include "stable.h"
#include "lepluginframeworkcontext.h"
#include "lepluginframework_p.h"

LePluginFrameworkContext::LePluginFrameworkContext()
    : plugins(NULL), systemPlugin(new LePluginFramework())
    , initialized(false)
{
    systemPlugin->LePlugin::init(new LePluginFrameworkPrivate(systemPlugin, this));
}

LePluginFrameworkContext::~LePluginFrameworkContext()
{
    if (initialized)
    {
        this->uninit();
    }
}

void LePluginFrameworkContext::init()
{
    LePluginFrameworkPrivate* const systemPluginPrivate = systemPlugin->d_func();
    systemPluginPrivate->initSystemPlugin();

    plugins = new LePlugins(this);

    initialized = true;
}

void LePluginFrameworkContext::uninit()
{
    if (!initialized) return;

    LePluginFrameworkPrivate* const systemPluginPrivate = systemPlugin->d_func();
    systemPluginPrivate->uninitSystemPlugin();

    plugins->clear();
    delete plugins;
    plugins = NULL;

    initialized = false;
}

void LePluginFrameworkContext::resolvePlugin(LePluginPrivate* plugin)
{

}
