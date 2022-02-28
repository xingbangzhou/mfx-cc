#include "stable.h"
#include "mainwindow.h"
#include "xhutils/framelesshelper.h"

MainWindow::MainWindow(QWidget* parent) 
    : QMainWindow(parent), m_framelessHelper(new FramelessHelper(this))
{
    initialize();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initialize()
{
    setWindowFlag(Qt::FramelessWindowHint);
    m_framelessHelper->addIncludeItem(this);
    m_framelessHelper->setTitleBarHeight(40);
    setMinimumSize({ 800, 600 });

    QPalette palette(palette());
    palette.setColor(QPalette::Window, QColor("#3a4055"));
    setAutoFillBackground(true);
    setPalette(palette);
}

