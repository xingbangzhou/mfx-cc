#include "stable.h"

#include <QApplication>
#include <QFile>
#include <QWindow>

#include "mainwindow.h"
#include "xhutils/framelesshelper.h"
#include "mainlayout.h"
#include "titlebar.h"
#include "leftbar.h"
#include "frameview.h"
#include "wkframework.h"
#include "bizcenter.h"

const int MinWindowWidth = 875;
const int MinWindowHeight = 625;

MainWindow::MainWindow(QWidget* parent) 
    : QMainWindow(parent)
    , m_titleBar(new TitleBar(this))
    , m_leftBar(new LeftBar(this))
    , m_frameView(new FrameView(this))
{
     initialize();
}

MainWindow::~MainWindow()
{

}

bool MainWindow::event(QEvent* ev)
{ 
    auto type = ev->type();
    switch (type)
    {
    case QEvent::WindowStateChange:
        m_titleBar->setMainMaximize(isMaximized());
        break;
    default:
        break;
    }

    return QMainWindow::event(ev);
}

void MainWindow::initialize()
{
    wkApp->setFrameView(m_frameView);
    // 自定义窗体
    setWindowFlag(Qt::FramelessWindowHint);
    setMinimumSize({ MinWindowWidth, MinWindowHeight });
    m_framelessHelper = new FramelessHelper(this);
    m_framelessHelper->setTitleBarHeight(32);
    QList<QWidget*> excludeItems;
    m_titleBar->getBtns(excludeItems);
    excludeItems.push_back(m_leftBar->avatar());
    for (auto item : excludeItems)
        m_framelessHelper->addExcludeItem(item);
    
    // 布局
    QWidget* widget = new QWidget(this);
    m_layout = new MainLayout(widget);
    m_layout->init(m_leftBar, m_titleBar, m_frameView);
    setCentralWidget(widget);

    // QSS主题
    QFile file(":/resources/theme/default.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    qApp->setStyleSheet(styleSheet);

    // 初始化数据
    wkApp->bizCenter()->init();
}

