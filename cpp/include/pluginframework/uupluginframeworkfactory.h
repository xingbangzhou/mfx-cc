#ifndef UUPLUGINFRAMEWORKFACTORY_H
#define UUPLUGINFRAMEWORKFACTORY_H

#include <QSharedPointer>

#include "pluginframework/uupluginfwexport.h"
#include "pluginframework/uupluginfw_global.h"

class uuPluginFramework;
class uuPluginFrameworkContext;

class UUPLUGINFW_EXPORT uuPluginFrameworkFactory
{
public:
    explicit uuPluginFrameworkFactory(const uuProperties& initProps = uuProperties());
    ~uuPluginFrameworkFactory();

    QSharedPointer<uuPluginFramework> getFramework();

private:
    uuPluginFrameworkContext* fwCtx;
};

#endif // UUPLUGINFRAMEWORKFACTORY_H
