#include "stable.h"
#include "cefcore/cefframework.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    CefFramework cef;

    cef.initialize(argc, argv);

    return cef.run();
}
