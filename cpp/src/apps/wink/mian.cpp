#include "stable.h"
#include "wkframework.h"
#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    WKFramework app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
