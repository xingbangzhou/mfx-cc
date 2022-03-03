#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>

class MainView : public QWidget
{
    Q_OBJECT

public:
    explicit MainView(QWidget* parent = nullptr);
    ~MainView();
};

#endif // MAINVIEW_H
