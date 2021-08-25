#ifndef XHPLUGINFRAMEWORK_H
#define XHPLUGINFRAMEWORK_H

#include <QMetaType>

#include "xhpluginfwexport.h"
#include "xhplugin.h"

class XhPluginFrameworkContext;
class XhPluginFrameworkPrivate;

class XHPLUGINFW_EXPORT XhPluginFramework : public XhPlugin
{
public:

    bool init();

    void start();

    void stop();
    // this method is empty
    void uninstall();

protected:

    friend class XhPluginFrameworkContext;

    XhPluginFramework();

private:
    Q_DECLARE_PRIVATE(XhPluginFramework)
    Q_DISABLE_COPY(XhPluginFramework)
};

#endif // XHPLUGINFRAMEWORK_H
