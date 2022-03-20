#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class FramelessHelper;

class TitleBar;
class LeftBar;
class FrameView;
class MainLayout;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    bool event(QEvent*) override;

private:
    void initialize();

    FramelessHelper* m_framelessHelper;
    MainLayout* m_layout;
    TitleBar* m_titleBar;
    LeftBar* m_leftBar;
    FrameView* m_frameView;
};
#endif // MAINWINDOW_H
