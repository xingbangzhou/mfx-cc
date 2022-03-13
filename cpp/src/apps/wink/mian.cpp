#include "stable.h"
#include "wkframework.h"
#include "mainwindow.h"

int main(int argc, char* argv[])
{
    WKFramework app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
