#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "framelesshelper.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    FramelessHelper* m_framelessHelper;
};
#endif // MAINWINDOW_H
