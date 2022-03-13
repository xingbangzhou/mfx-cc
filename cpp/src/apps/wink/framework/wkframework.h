#ifndef WKFRAMEWORK_H
#define WKFRAMEWORK_H

#include <QApplication>
#include <QScopedPointer>

class BizCenter;
class MainWindow;

#define wkApp (static_cast<WKFramework*>(QCoreApplication::instance()))

class WKFramework : public QApplication
{
    Q_OBJECT
public:
    WKFramework(int& argc, char** argv);
    ~WKFramework();

    void showWindow();

    BizCenter* bizCenter() const;

private:
    QScopedPointer<MainWindow> m_mainWindow;
};

#endif // WKFRAMEWORK_H
