#ifndef UUPLUGINFRAMEWORK_H
#define UUPLUGINFRAMEWORK_H

#include <QMetaType>

#include "uupluginfwexport.h"
#include "uuplugin.h"

class uuPluginFrameworkContext;
class uuPluginFrameworkPrivate;

class UUPLUGINFW_EXPORT uuPluginFramework : public uuPlugin
{
public:

    bool init();

    void start();

    void stop();
    // this method is empty
    void uninstall();

protected:

    friend class uuPluginFrameworkContext;

    uuPluginFramework();

private:
    Q_DECLARE_PRIVATE(uuPluginFramework)
    Q_DISABLE_COPY(uuPluginFramework)
};

#endif // UUPLUGINFRAMEWORK_H
