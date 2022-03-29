#ifndef MP4VIEW_H
#define MP4VIEW_H

#include <QWidget>

class MP4View : public QWidget
{
    Q_OBJECT
public:
    MP4View();
    ~MP4View();

protected:
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent*) override;

private:

};

#endif // MP4VIEW_H
