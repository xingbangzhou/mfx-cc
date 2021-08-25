#include "stable.h"
#include "xhpluginframeworkcontext.h"
#include "xhpluginframework_p.h"
#include "xhservices.h"

XhPluginFrameworkContext::XhPluginFrameworkContext()
    : plugins(nullptr), listeners(this), services(nullptr),
      systemPlugin(new XhPluginFramework()),
      m_initialized(false), m_logger("XhPluginFramework")
{
    systemPlugin->XhPlugin::init(new XhPluginFrameworkPrivate(systemPlugin, this));
}

XhPluginFrameworkContext::~XhPluginFrameworkContext()
{
    if (m_initialized)
    {
        this->uninit();
    }
}

void XhPluginFrameworkContext::init()
{
    XhPluginFrameworkPrivate* const systemPluginPrivate = systemPlugin->d_func();
    systemPluginPrivate->initSystemPlugin();

    plugins = new XhPlugins(this);
    services = new XhServices(this);

    m_initialized = true;
}

void XhPluginFrameworkContext::uninit()
{
    if (!m_initialized) return;

    XhPluginFrameworkPrivate* const systemPluginPrivate = systemPlugin->d_func();
    systemPluginPrivate->uninitSystemPlugin();

    plugins->clear();
    delete plugins;
    plugins = nullptr;

    delete services;
    services = nullptr;

    m_initialized = false;
}

void XhPluginFrameworkContext::resolvePlugin(XhPluginPrivate* plugin)
{
	plugin;
}

XhLogger& XhPluginFrameworkContext::logger()
{
	return m_logger;
}
