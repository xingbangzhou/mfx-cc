#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QPushButton>
#include <QList>

class FlatButton : public QPushButton
{
    Q_OBJECT
public:
    explicit FlatButton(QWidget* parent);
    ~FlatButton();

protected:
    void paintEvent(QPaintEvent*) override;
};

class QPushButton;
class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget* parent = nullptr);
    ~TitleBar();

    void setMainMaximize(bool flag);

    void getBtns(QList<QWidget*>& out) const;

private slots:
    void closed();
    void maximized();
    void minized();

private:
    bool m_mainMaximize;
    
    FlatButton* m_btnClose;
    FlatButton* m_btnMaximize;
    FlatButton* m_btnMinimize;
};

#endif // TITLEBAR_H
