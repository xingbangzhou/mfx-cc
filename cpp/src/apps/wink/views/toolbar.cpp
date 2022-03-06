#include "stable.h"
#include "toolbar.h"

#include <QStyleOption>
#include <QPainter>

ToolBar::ToolBar(QWidget* parent)
    : QWidget(parent)
{
    setObjectName("ToolBar");
}

ToolBar::~ToolBar()
{

}

void ToolBar::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QStyleOption styleOpt;
    styleOpt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}
