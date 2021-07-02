#ifndef LEPLUGINFRAMEWORK_H
#define LEPLUGINFRAMEWORK_H

#include <QMetaType>

#include "lepluginfwexport.h"
#include "leplugin.h"

class LePluginFrameworkContext;
class LePluginFrameworkPrivate;

class LEPLUGINFW_EXPORT LePluginFramework : public LePlugin
{
public:

    bool init();

    void start();

    void stop();
    // this method is empty
    void uninstall();

protected:

    friend class LePluginFrameworkContext;

    LePluginFramework();

private:
    Q_DECLARE_PRIVATE(LePluginFramework)
    Q_DISABLE_COPY(LePluginFramework)
};

#endif // LEPLUGINFRAMEWORK_H
