#include "stable.h"
#include "pluginframework/uupluginframework.h"
#include "uupluginframework_p.h"

uuPluginFramework::uuPluginFramework()
    : uuPlugin()
{
    qRegisterMetaType<QSharedPointer<uuPlugin> >("QSharedPointer<uuPlugin>");
}

void uuPluginFramework::init()
{
    Q_D(uuPluginFramework);

    uuPluginPrivate::Locker sync(&d->lock);
    d->waitOnOperation(&d->lock, "Framework.init", true);
    switch (d->state)
    {
    case uuPlugin::INSTALLED:
    case uuPlugin::RESOLVED:
        break;
    case uuPlugin::STARTING:
    case uuPlugin::ACTIVE:
        return;
    }
    d->init();
}
