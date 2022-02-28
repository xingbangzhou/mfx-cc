#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

class FramelessHelper;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initialize();

    FramelessHelper* m_framelessHelper;
};
#endif // MAINWINDOW_H
