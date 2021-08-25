#include "stable.h"
#include "xhpluginframework/xhpluginframeworkfactory.h"

#include "xhpluginframeworkcontext.h"

XhPluginFrameworkFactory::XhPluginFrameworkFactory()
    : fwCtx(nullptr)
{
    fwCtx = new XhPluginFrameworkContext();
}

XhPluginFrameworkFactory::~XhPluginFrameworkFactory()
{
    fwCtx->uninit();
    delete fwCtx;
}

QSharedPointer<XhPluginFramework> XhPluginFrameworkFactory::getFramework()
{
    return fwCtx->systemPlugin;
}
