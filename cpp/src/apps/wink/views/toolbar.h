#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit ToolBar(QWidget* parent = nullptr);
    ~ToolBar();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
};

#endif // TOOLBAR_H
