#include "stable.h"
#include "uupluginframework_p.h"
#include "pluginframework/uuplugin_constants.h"
#include "uupluginframeworkcontext_p.h"
#include "pluginframework/uuplugincontext.h"

uuPluginFrameworkPrivate::uuPluginFrameworkPrivate(QWeakPointer<uuPlugin> qq, uuPluginFrameworkContext* fw)
    : uuPluginPrivate(qq, fw, uuPluginConstants::SYSTEM_PLUGIN_LOCATION)
{

}

void uuPluginFrameworkPrivate::init()
{
    this->state = uuPlugin::STARTING;
    this->fwCtx->init();
}

void uuPluginFrameworkPrivate::initSystemPlugin()
{
    this->pluginContext.reset(new uuPluginContext(this));
}

void uuPluginFrameworkPrivate::uninitSystemPlugin()
{

}
