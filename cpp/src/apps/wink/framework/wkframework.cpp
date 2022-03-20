#include "stable.h"
#include "wkframework.h"
#include "mainwindow.h"
#include "bizcenter.h"
#include "usercenter.h"

WKFramework::WKFramework(int& argc, char** argv) 
    : QApplication(argc, argv)
{

}

WKFramework::~WKFramework()
{

}

UserCenter* WKFramework::userCenter() const
{
    static UserCenter _userCenter;
    return &_userCenter;
}

BizCenter* WKFramework::bizCenter() const
{
    static BizCenter _bizCenter;
    return &_bizCenter;
}
