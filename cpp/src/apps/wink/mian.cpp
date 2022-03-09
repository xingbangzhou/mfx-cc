#include "stable.h"
#include "wkframework.h"
#include "mainwindow.h"

extern "C"
{
    #include <libavcodec/avcodec.h>
}
#pragma comment(lib, "avcodec.lib")

int main(int argc, char* argv[])
{
    WKFramework app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
