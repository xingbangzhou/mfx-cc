#ifndef WKFRAMEWORK_H
#define WKFRAMEWORK_H

#include <QApplication>
#include <QScopedPointer>
#include "xhcore/xhlogger.h"

#define wkApp (static_cast<wkFramework*>(QCoreApplication::instance()))
#define wkLogger (wkApp->logger())

class UserCenter;
class BizCenter;
class FrameView;
class wkFramework : public QApplication
{
    Q_OBJECT
public:
    wkFramework(int& argc, char** argv);
    ~wkFramework();

    xhLogger* logger();
    
    UserCenter* userCenter() const;
    
    BizCenter* bizCenter() const;
    
    void setFrameView(FrameView* view);
    FrameView* frameView() const;

private:
    FrameView* m_view;
};

#endif // WKFRAMEWORK_H
