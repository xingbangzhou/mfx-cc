#include "stable.h"
#include "mp4view.h"

#include <QPalette>

MP4View::MP4View()
{
    QPalette pal(palette());
    pal.setColor(QPalette::Window, QColor("#FF00FF"));
    setPalette(pal);
}

MP4View::~MP4View()
{

}
