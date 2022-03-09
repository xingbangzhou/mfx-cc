#include "stable.h"
#include "titlebar.h"

#include <QApplication>
#include <QBoxLayout>
#include <QVariant>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>

FlatButton::FlatButton(QWidget* parent) 
    : QPushButton(parent)
{

}

FlatButton::~FlatButton()
{
}

void FlatButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QStyleOption styleOpt;
    styleOpt.initFrom(this);
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    style()->drawPrimitive(QStyle::PE_PanelButtonCommand, &styleOpt, &painter, this);
}

TitleBar::TitleBar(QWidget* parent) 
    : QWidget(parent)
    , m_mainMaximize(false)
{
    setObjectName(QString("TitleBar"));

    m_btnMinimize = new FlatButton(this);
    m_btnMinimize->setObjectName("minimize");
    connect(m_btnMinimize, SIGNAL(clicked(bool)), this, SLOT(minized()));
    m_btnMaximize = new FlatButton(this);
    m_btnMaximize->setObjectName("maximize");
    connect(m_btnMaximize, SIGNAL(clicked(bool)), this, SLOT(maximized()));
    m_btnClose = new FlatButton(this);
    m_btnClose->setObjectName("close");
    connect(m_btnClose, SIGNAL(clicked(bool)), this, SLOT(closed()));

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addStretch(1);
    layout->addWidget(m_btnMinimize);
    layout->addWidget(m_btnMaximize);
    layout->addWidget(m_btnClose);
    setLayout(layout);

    setMainMaximize(parent->isMaximized());
}

TitleBar::~TitleBar()
{

}

void TitleBar::setMainMaximize(bool flag)
{
    if (m_mainMaximize != flag)
    {
        m_mainMaximize = flag;
        m_btnMaximize->setProperty("maximizeProperty", QVariant(flag));
        qApp->style()->unpolish(m_btnMaximize);
        qApp->style()->polish(m_btnMaximize);
        m_btnMaximize->update();
    }
}

void TitleBar::getBtns(QList<QWidget*>& out) const
{
    out.append(m_btnClose);
    out.append(m_btnMaximize);
    out.append(m_btnMinimize);
}

void TitleBar::closed()
{
    qApp->quit();
}

void TitleBar::maximized()
{
    auto topWidget = parentWidget()->parentWidget();
    auto flag = topWidget->isMaximized();
    flag ? topWidget->showNormal() : topWidget->showMaximized();
}

void TitleBar::minized()
{
    auto topWidget = parentWidget()->parentWidget();
    topWidget->showMinimized();
}
