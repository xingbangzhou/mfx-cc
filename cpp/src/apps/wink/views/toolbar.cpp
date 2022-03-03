#include "stable.h"
#include "toolbar.h"

ToolBar::ToolBar(QWidget* parent /* = nullptr */) : QWidget(parent)
{
    QPalette palette(this->palette());
    palette.setColor(QPalette::Window, QColor(46,46,46));
    setAutoFillBackground(true);
    setPalette(palette);
}

ToolBar::~ToolBar()
{

}
