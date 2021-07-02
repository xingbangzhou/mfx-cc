#ifndef LEPLUGINACTIVATOR_H
#define LEPLUGINACTIVATOR_H

#include "leplugincontext.h"

class LePluginActivator
{
public:
    virtual ~LePluginActivator() {}

    virtual void start(LePluginContext* context) = 0;

    virtual void stop(LePluginContext* context) = 0;
};

Q_DECLARE_INTERFACE(LePluginActivator, "org.uu.pluginfw.pluginactivator")

#endif // LEPLUGINACTIVATOR_H
