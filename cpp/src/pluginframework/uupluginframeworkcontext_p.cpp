#include "stable.h"
#include "uupluginframeworkcontext_p.h"
#include "uupluginframework_p.h"

uuPluginFrameworkContext::uuPluginFrameworkContext()
    : plugins(NULL), systemPlugin(new uuPluginFramework())
    , initialized(false)
{
    systemPlugin->uuPlugin::init(new uuPluginFrameworkPrivate(systemPlugin, this));
}

uuPluginFrameworkContext::~uuPluginFrameworkContext()
{
    if (initialized)
    {
        this->uninit();
    }
}

void uuPluginFrameworkContext::init()
{
    uuPluginFrameworkPrivate* const systemPluginPrivate = systemPlugin->d_func();
    systemPluginPrivate->initSystemPlugin();

    plugins = new uuPlugins(this);

    initialized = true;
}

void uuPluginFrameworkContext::uninit()
{
    if (!initialized) return;

    uuPluginFrameworkPrivate* const systemPluginPrivate = systemPlugin->d_func();
    systemPluginPrivate->uninitSystemPlugin();

    plugins->clear();
    delete plugins;
    plugins = NULL;

    initialized = false;
}
