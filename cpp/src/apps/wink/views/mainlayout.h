#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

#include <QLayout>

const QSize MinLayoutSize = { 875, 625 };

class MainLayout : public QLayout
{
    Q_OBJECT
public:
    explicit MainLayout(QWidget* parent);
    ~MainLayout();

    void init(QWidget* leftBar, QWidget* titleBar, QWidget* mainView);

    // QLayout
    void addItem(QLayoutItem* item) override;
    QSize sizeHint() const override;
    QSize minimumSize() const override;
    int count() const override;
    QLayoutItem* itemAt(int) const override;
    QLayoutItem* takeAt(int) override;
    void setGeometry(const QRect& r) override;

private:
    QVector<QLayoutItem*> m_items;
};

#endif // MAINLAYOUT_H
