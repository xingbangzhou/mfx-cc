#ifndef LEPLUGINFRAMEWORKPRIVATE_H
#define LEPLUGINFRAMEWORKPRIVATE_H

#include "leplugin_p.h"
#include "lepluginframework/lepluginframework.h"

class LePluginFrameworkPrivate : public LePluginPrivate
{
public:

    LockObject lock;

    LePluginFrameworkPrivate(QWeakPointer<LePlugin> qq, LePluginFrameworkContext* fw);

    void init();

    void initSystemPlugin();

    void uninitSystemPlugin();

    void activate(LePluginContext* context);
    void deactivate(LePluginContext* context);

    void shutdown();

private:

    void shutdown0(bool wasActive);

    void stopAllPlugins();
};

#endif // LEPLUGINFRAMEWORKPRIVATE_H
