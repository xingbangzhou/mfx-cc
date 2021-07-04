#include "stable.h"
#include "lepluginframeworkcontext.h"
#include "lepluginframework_p.h"
#include "leservices.h"

LePluginFrameworkContext::LePluginFrameworkContext()
    : plugins(NULL), listeners(this), services(NULL),
      systemPlugin(new LePluginFramework()),
      m_initialized(false)
{
    systemPlugin->LePlugin::init(new LePluginFrameworkPrivate(systemPlugin, this));
}

LePluginFrameworkContext::~LePluginFrameworkContext()
{
    if (m_initialized)
    {
        this->uninit();
    }
}

void LePluginFrameworkContext::init()
{
    LePluginFrameworkPrivate* const systemPluginPrivate = systemPlugin->d_func();
    systemPluginPrivate->initSystemPlugin();

    plugins = new LePlugins(this);
    services = new LeServices(this);

    m_initialized = true;
}

void LePluginFrameworkContext::uninit()
{
    if (!m_initialized) return;

    LePluginFrameworkPrivate* const systemPluginPrivate = systemPlugin->d_func();
    systemPluginPrivate->uninitSystemPlugin();

    plugins->clear();
    delete plugins;
    plugins = NULL;

    delete services;
    services = NULL;

    m_initialized = false;
}

void LePluginFrameworkContext::resolvePlugin(LePluginPrivate* plugin)
{

}
