#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class FramelessHelper;
class MainLayout;
class BizView;
class TitleBar;
class MainView;
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
    BizView* m_bizView;
    TitleBar* m_titleBar;
    MainView* m_mainView;
};
#endif // MAINWINDOW_H
