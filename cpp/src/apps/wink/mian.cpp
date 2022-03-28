#include "stable.h"
#include "wkframework.h"
#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    wkFramework app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
