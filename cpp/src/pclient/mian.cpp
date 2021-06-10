#include "stable.h"
#include "cefcore/cefframework.h"

#include <QApplication>

int qt_loop()
{
    return qApp->exec();
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    CefFramework cef;

    cef.initialize(argc, argv);

    cef.messageLoopEx()->setRunner(qt_loop);

    return cef.run();
}
