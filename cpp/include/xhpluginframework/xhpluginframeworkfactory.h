#ifndef XHPLUGINFRAMEWORKFACTORY_H
#define XHPLUGINFRAMEWORKFACTORY_H

#include <QSharedPointer>

#include "xhpluginfwexport.h"
#include "xhpluginframework.h"

class XhPluginFrameworkContext;

class XHPLUGINFW_EXPORT XhPluginFrameworkFactory
{
public:
    XhPluginFrameworkFactory();
    ~XhPluginFrameworkFactory();

    QSharedPointer<XhPluginFramework> getFramework();

private:

    XhPluginFrameworkContext* fwCtx;
};

#endif // XHPLUGINFRAMEWORKFACTORY_H
