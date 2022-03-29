#include "stable.h"
#include "mp4view.h"

#include <QPalette>
#include <QDebug>
#include <QPainter>

MP4View::MP4View()
{

}

MP4View::~MP4View()
{

}

void MP4View::paintEvent(QPaintEvent* ev)
{
    Q_UNUSED(ev);

    QPainter painter(this);
    auto brush = QBrush(Qt::red);
    painter.setBrush(brush);

    painter.drawRect(rect());

}

void MP4View::resizeEvent(QResizeEvent*)
{

}
