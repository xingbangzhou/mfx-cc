#ifndef WKFRAMEWORK_H
#define WKFRAMEWORK_H

#include <QApplication>
#include <QScopedPointer>

#define wkApp (static_cast<WKFramework*>(QCoreApplication::instance()))

class UserCenter;
class BizCenter;
class WKFramework : public QApplication
{
    Q_OBJECT
public:
    WKFramework(int& argc, char** argv);
    ~WKFramework();

    UserCenter* userCenter() const;

    BizCenter* bizCenter() const;

private:
};

#endif // WKFRAMEWORK_H
