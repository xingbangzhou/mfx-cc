#ifndef XHPLUGINACTIVATOR_H
#define XHPLUGINACTIVATOR_H

#include "xhplugincontext.h"

class XhPluginActivator
{
public:
    virtual ~XhPluginActivator() {}

    virtual void start(XhPluginContext* context) = 0;

    virtual void stop(XhPluginContext* context) = 0;
};

Q_DECLARE_INTERFACE(XhPluginActivator, "org.uu.pluginfw.pluginactivator")

#endif // XHPLUGINACTIVATOR_H
