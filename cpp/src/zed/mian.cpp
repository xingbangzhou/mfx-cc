#include "stable.h"
#include <QApplication>

#include "cefcore/cefframework.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    CefFramework cef;

    cef.init(argc, argv);
    cef.setMsgLoop([]() -> void { qApp->exec(); });
    
    cef.exec();
    return 0;
}
