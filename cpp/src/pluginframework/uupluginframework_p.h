#ifndef UUPLUGINFRAMEWORKPRIVATE_H
#define UUPLUGINFRAMEWORKPRIVATE_H

#include "uuplugin_p.h"
#include "pluginframework/uupluginframework.h"

class uuPluginFrameworkPrivate : public uuPluginPrivate
{
public:

    LockObject lock;

    uuPluginFrameworkPrivate(QWeakPointer<uuPlugin> qq, uuPluginFrameworkContext* fw);

    void init();

    void initSystemPlugin();

    void uninitSystemPlugin();
};

#endif // UUPLUGINFRAMEWORKPRIVATE_H
