#include "stable.h"
#include "wkframework.h"
#include "mainwindow.h"
#include "bizcenter.h"

WKFramework::WKFramework(int& argc, char** argv) 
    : QApplication(argc, argv)
    , m_mainWindow(new MainWindow())
{
}

WKFramework::~WKFramework()
{
}

void WKFramework::showWindow()
{
    m_mainWindow->show();
}

BizCenter* WKFramework::bizCenter() const
{
    static BizCenter _bizCenter;
    return &_bizCenter;
}
