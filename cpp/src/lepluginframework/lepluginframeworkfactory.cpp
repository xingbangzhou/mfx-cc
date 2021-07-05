#include "stable.h"
#include "lepluginframework/lepluginframeworkfactory.h"

#include "lepluginframeworkcontext.h"

LePluginFrameworkFactory::LePluginFrameworkFactory()
    : fwCtx(nullptr)
{
    fwCtx = new LePluginFrameworkContext();
}

LePluginFrameworkFactory::~LePluginFrameworkFactory()
{
    fwCtx->uninit();
    delete fwCtx;
}

QSharedPointer<LePluginFramework> LePluginFrameworkFactory::getFramework()
{
    return fwCtx->systemPlugin;
}
