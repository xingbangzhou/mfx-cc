#include "stable.h"

#include <QApplication>
#include <iostream>

#include "pluginframework/uupluginframeworkfactory.h"
#include "pluginframework/uuplugincontext.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    uuPluginFrameworkFactory fwFactory;
    QSharedPointer<uuPluginFramework> framework = fwFactory.getFramework();

    framework->init();
    
    qApp->addLibraryPath(qApp->applicationDirPath() + "/");

    std::cout << qApp->applicationDirPath().toStdString() + "/pluginkafka.dll" << std::endl;
    QSharedPointer<uuPlugin> plugin = framework->getPluginContext()->installPlugin(QUrl::fromLocalFile(qApp->applicationDirPath() + "/pluginkafka.dll"));
    
    framework->start();

    plugin->start();

    return app.exec();
}
