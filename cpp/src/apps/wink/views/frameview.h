#ifndef FRAMEVIEW_H
#define FRAMEVIEW_H

#include <QWidget>

class FrameView : public QWidget
{
    Q_OBJECT

public:
    explicit FrameView(QWidget* parent = nullptr);
    ~FrameView();

    void setView(QWidget* content);

protected:
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent*) override;

private:
    QWidget* m_content;
};

#endif // FRAMEVIEW_H
