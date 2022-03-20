#ifndef FRAMEVIEW_H
#define FRAMEVIEW_H

#include <QWidget>

class FrameView : public QWidget
{
    Q_OBJECT

public:
    explicit FrameView(QWidget* parent = nullptr);
    ~FrameView();
};

#endif // FRAMEVIEW_H
