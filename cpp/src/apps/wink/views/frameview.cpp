#include "stable.h"
#include "frameview.h"

#include <QGridLayout>
#include <QDebug>
#include "QStyleOption"
#include "QPainter"

FrameView::FrameView(QWidget* parent /* = nullptr */)
    : QWidget(parent)
    , m_content(nullptr)
{
    setMinimumSize({ 400, 500 });
    setObjectName("FrameView");
    QGridLayout* layout = new QGridLayout(this);
    setLayout(layout);
}

FrameView::~FrameView()
{

}

void FrameView::setView(QWidget* content)
{
    if (m_content)
    {
        m_content->hide();
        layout()->removeWidget(m_content);
    }
    m_content = content;
    if (m_content)
    {
        m_content->setParent(this);
        layout()->addWidget(m_content);
        m_content->setVisible(true);
    }
}

void FrameView::paintEvent(QPaintEvent*)
{
    QStyleOption styleOpt;
    styleOpt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}

void FrameView::resizeEvent(QResizeEvent* ev)
{
    QWidget::resizeEvent(ev);
}
