#include "stable.h"

#include <QApplication>

int qt_loop()
{
    return qApp->exec();
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    return app.exec();
}
