#ifndef UUPLUGINFRAMEWORKCONTEXT_P_H
#define UUPLUGINFRAMEWORKCONTEXT_P_H

#include "pluginframework/uupluginframework.h"
#include "uuplugins_p.h"

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

#endif // UUPLUGINFRAMEWORKCONTEXT_P_H
