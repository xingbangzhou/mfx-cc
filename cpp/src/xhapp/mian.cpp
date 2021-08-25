#include "stable.h"
#include "xhmainframe.h"

#include <QApplication>
#include <QTimer>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    LeMainFrame mainframe;

    mainframe.startFramework();

    mainframe.testService();

    return app.exec();
}
