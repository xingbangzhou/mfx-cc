#ifndef WKFRAMEWORK_H
#define WKFRAMEWORK_H

#include <QApplication>

class WKFramework : public QApplication
{
    Q_OBJECT
public:
    WKFramework(int& argc, char** argv);
    ~WKFramework();
};

#endif // WKFRAMEWORK_H
