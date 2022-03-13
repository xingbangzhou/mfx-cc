#include "stable.h"
#include "mainwindow.h"

#include "xhutils/framelesshelper.h"
#include "mainlayout.h"
#include "titlebar.h"
#include "bizview.h"
#include "mainview.h"

#include <QFile>
#include <QApplication>
#include <QMoveEvent>

const int MinWindowWidth = 875;
const int MinWindowHeight = 625;

MainWindow::MainWindow(QWidget* parent) 
    : QMainWindow(parent)
    , m_titleBar(new TitleBar(this))
    , m_bizView(new BizView(this))
    , m_mainView(new MainView(this))
{
     initialize();
}

MainWindow::~MainWindow()
{

}

bool MainWindow::event(QEvent* ev)
{
   bool result = QMainWindow::event(ev);

    if (ev->type() == QEvent::WindowStateChange)
    {
        m_titleBar->setMainMaximize(isMaximized());
    }

    return result;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
}

void MainWindow::moveEvent(QMoveEvent* event)
{
    QMainWindow::moveEvent(event);
}

void MainWindow::initialize()
{
    // 自定义窗体
    setWindowFlag(Qt::FramelessWindowHint);
    setMinimumSize({ MinWindowWidth, MinWindowHeight });
    m_framelessHelper = new FramelessHelper(this);
    m_framelessHelper->setTitleBarHeight(32);
    QList<QWidget*> excludeItems;
    m_titleBar->getBtns(excludeItems);
    excludeItems.push_back(m_bizView->avatar());
    for (auto item : excludeItems)
        m_framelessHelper->addExcludeItem(item);
    m_framelessHelper->addExcludeItem(m_bizView);
    
    // 布局
    QWidget* widget = new QWidget(this);
    m_layout = new MainLayout(widget);
    m_layout->init(m_bizView, m_titleBar, m_mainView);
    setCentralWidget(widget);

    // 窗口主题颜色
    QFile file(":/resources/qss/default.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    qApp->setStyleSheet(styleSheet);
}

