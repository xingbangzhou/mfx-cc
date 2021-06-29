#ifndef UUPLUGINFRAMEWORKFACTORY_H
#define UUPLUGINFRAMEWORKFACTORY_H

#include <QSharedPointer>

#include "pluginframework/uupluginfwexport.h"

class uuPluginFramework;
class uuPluginFrameworkContext;

class UUPLUGINFW_EXPORT uuPluginFrameworkFactory
{
public:
    uuPluginFrameworkFactory();
    ~uuPluginFrameworkFactory();

    QSharedPointer<uuPluginFramework> getFramework();

private:

    uuPluginFrameworkContext* fwCtx;
};

#endif // UUPLUGINFRAMEWORKFACTORY_H
