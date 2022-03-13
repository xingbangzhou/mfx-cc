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

#ifdef Q_OS_WINDOWS
#include <windows.h>

#endif // OS_WINDOWS


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

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    auto isMaximize = isMaximized();
    m_titleBar->setMainMaximize(isMaximize);

#ifdef Q_OS_WINDOWS
    if (isMaximize)
        return;

    const HWND hwnd = reinterpret_cast<HWND>(winId());
    WINDOWPLACEMENT windowPlacement;
    windowPlacement.length = sizeof(WINDOWPLACEMENT);
    GetWindowPlacement(hwnd, &windowPlacement);
    auto plw = windowPlacement.rcNormalPosition.right - windowPlacement.rcNormalPosition.left;
    auto plh = windowPlacement.rcNormalPosition.bottom - windowPlacement.rcNormalPosition.top;

    if ( width() < plw || height() < plh)
    {
        resize(plw, plh);
    }

#endif // Q_OS_WINDOWS
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

