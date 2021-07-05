#include "stable.h"
#include "lepluginframeworkcontext.h"
#include "lepluginframework_p.h"
#include "leservices.h"

LePluginFrameworkContext::LePluginFrameworkContext()
    : plugins(nullptr), listeners(this), services(nullptr),
      systemPlugin(new LePluginFramework()),
      m_initialized(false), m_logger("LePluginFramework")
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
    plugins = nullptr;

    delete services;
    services = nullptr;

    m_initialized = false;
}

void LePluginFrameworkContext::resolvePlugin(LePluginPrivate* plugin)
{
	plugin;
}

LeLogger& LePluginFrameworkContext::logger()
{
	return m_logger;
}
