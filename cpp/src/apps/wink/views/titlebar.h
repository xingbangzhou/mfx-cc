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

    void getBtns(QList<QWidget*>& out) const;

private slots:
    void closed();
    void minmaxed();
    void minized();

private:
    QPushButton* m_closeBtn;
    QPushButton* m_minmaxBtn;
    QPushButton* m_minizeBtn;
};

#endif // TITLEBAR_H
