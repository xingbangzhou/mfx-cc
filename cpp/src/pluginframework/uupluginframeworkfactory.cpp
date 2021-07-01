#include "stable.h"
#include "pluginframework/uupluginframeworkfactory.h"

#include "uupluginframeworkcontext.h"

uuPluginFrameworkFactory::uuPluginFrameworkFactory()
    : fwCtx(NULL)
{
    fwCtx = new uuPluginFrameworkContext();
}

uuPluginFrameworkFactory::~uuPluginFrameworkFactory()
{
    fwCtx->uninit();
    delete fwCtx;
}

QSharedPointer<uuPluginFramework> uuPluginFrameworkFactory::getFramework()
{
    return fwCtx->systemPlugin;
}
