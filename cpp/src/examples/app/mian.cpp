#include "stable.h"
#include "framework.h"
#include "mainwindow.h"

#include <QApplication>
#include <QTimer>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    FrameWork frameWork;
    MainWindow mainWindow;

    frameWork.init();

    mainWindow.show();

    return app.exec();
}
