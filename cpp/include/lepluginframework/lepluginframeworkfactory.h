#ifndef LEPLUGINFRAMEWORKFACTORY_H
#define LEPLUGINFRAMEWORKFACTORY_H

#include <QSharedPointer>

#include "lepluginfwexport.h"
#include "lepluginframework.h"

class LePluginFrameworkContext;

class LEPLUGINFW_EXPORT LePluginFrameworkFactory
{
public:
    LePluginFrameworkFactory();
    ~LePluginFrameworkFactory();

    QSharedPointer<LePluginFramework> getFramework();

private:

    LePluginFrameworkContext* fwCtx;
};

#endif // LEPLUGINFRAMEWORKFACTORY_H
