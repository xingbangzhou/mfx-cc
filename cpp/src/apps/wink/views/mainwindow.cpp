#include "stable.h"
#include "mainwindow.h"

#include "xhutils/framelesshelper.h"
#include "mainlayout.h"
#include "titlebar.h"
#include "toolbar.h"
#include "mainview.h"

#include <QFile>
#include <QApplication>

const int MinWindowWidth = 875;
const int MinWindowHeight = 625;

MainWindow::MainWindow(QWidget* parent) 
    : QMainWindow(parent)
    , m_framelessHelper(new FramelessHelper(this))
    , m_titleBar(new TitleBar(this))
    , m_toolBar(new ToolBar(this))
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
    m_titleBar->setMainMaximize(isMaximized());
}

void MainWindow::initialize()
{
    // 自定义窗体
    setWindowFlag(Qt::FramelessWindowHint);
    setMinimumSize({ MinWindowWidth, MinWindowHeight });
    m_framelessHelper->setTitleBarHeight(48);
    QList<QWidget*> btns;
    m_titleBar->getBtns(btns);
    for (auto btn : btns)
        m_framelessHelper->addExcludeItem(btn);
    m_framelessHelper->addExcludeItem(m_toolBar);
    
    // 布局
    QWidget* widget = new QWidget(this);
    m_layout = new MainLayout(widget);
    m_layout->addWidget(m_toolBar);
    m_layout->addWidget(m_titleBar);
    m_layout->addWidget(m_mainView);
    setCentralWidget(widget);

    // 窗口主题颜色
    QFile file(":/resources/qss/default.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    qApp->setStyleSheet(styleSheet);
}

