#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QList>

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
    QPushButton* m_btnClose;
    QPushButton* m_btnMaximize;
    QPushButton* m_btnMinimize;
};

#endif // TITLEBAR_H
