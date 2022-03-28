#include "stable.h"
#include "wkframework.h"
#include "mainwindow.h"
#include "bizcenter.h"
#include "usercenter.h"

wkFramework::wkFramework(int& argc, char** argv) 
    : QApplication(argc, argv)
    , m_view(nullptr)
{

}

wkFramework::~wkFramework()
{

}

xhLogger* wkFramework::logger()
{
    static xhLogger _logger("wkApp");
    return &_logger;
}

UserCenter* wkFramework::userCenter() const
{
    static UserCenter _userCenter;
    return &_userCenter;
}

BizCenter* wkFramework::bizCenter() const
{
    static BizCenter _bizCenter;
    return &_bizCenter;
}

void wkFramework::setFrameView(FrameView* view)
{
    m_view = view;
}

FrameView* wkFramework::frameView() const
{
    return m_view;
}
