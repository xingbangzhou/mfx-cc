#ifndef UUPLUGINFRAMEWORKCONTEXT_H
#define UUPLUGINFRAMEWORKCONTEXT_H

#include "pluginframework/uupluginframework.h"
#include "uuplugins.h"

class uuPluginFrameworkContext
{
public:

    uuPlugins* plugins;

    QSharedPointer<uuPluginFramework> systemPlugin;

    uuPluginFrameworkContext();
    ~uuPluginFrameworkContext();

    void init();

    void uninit();

private:
    bool initialized;
};

#endif // UUPLUGINFRAMEWORKCONTEXT_H
