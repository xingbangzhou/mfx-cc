#ifndef UUPLUGINACTIVATOR_H
#define UUPLUGINACTIVATOR_H

#include "uuplugincontext.h"

class uuPluginActivator
{
public:
    virtual ~uuPluginActivator() {}

    virtual void start(uuPluginContext* context);

    virtual void stop(uuPluginContext* context) = 0;
};

Q_DECLARE_INTERFACE(uuPluginActivator, "org.uu.pluginfw.pluginactivator")

#endif // UUPLUGINACTIVATOR_H
