#include "stable.h"
#include "mainlayout.h"

MainLayout::MainLayout(QWidget* parent) 
    : QLayout(parent)
{

}

MainLayout::~MainLayout()
{
    QLayoutItem* item = nullptr;
    while ((item = takeAt(0))) 
        delete item;
}

void MainLayout::init(QWidget* leftBar, QWidget* titleBar, QWidget* mainView)
{
    addWidget(leftBar);
    addWidget(titleBar);
    addWidget(mainView);
}

void MainLayout::addItem(QLayoutItem* item)
{
    m_items.append(item);
}

QSize MainLayout::sizeHint() const
{
    QSize s(0, 0);
    int n = m_items.count();
    if (n > 0) 
        s = MinLayoutSize;
    int i = 0;
    while (i < n)
    {
        QLayoutItem* o = m_items.at(i);
        s = s.expandedTo(o->sizeHint());
        ++i;
    }
    return s;
}

QSize MainLayout::minimumSize() const
{
    QSize s(0, 0);
    int n = m_items.count();
    int i = 0;
    while (i < n)
    {
        QLayoutItem* o = m_items.at(i);
        s = s.expandedTo(o->minimumSize());
        ++i;
    }
    return s;
}

int MainLayout::count() const
{
    return m_items.size();
}

QLayoutItem* MainLayout::itemAt(int idx) const
{
    return m_items.value(idx);
}

QLayoutItem* MainLayout::takeAt(int idx)
{
    return idx >= 0 && idx < m_items.size() ? m_items.takeAt(idx) : nullptr;
}

void MainLayout::setGeometry(const QRect& r)
{
    QLayout::setGeometry(r);

    if (m_items.size() == 0)
        return;

    auto x = r.x(), y = r.y(), w = r.width(), h = r.height();
    auto lw = 60, th = 32;
    QLayoutItem* item = m_items[0];
    item->setGeometry({ { x, y }, QSize{ lw, h } });
    item = m_items[1];
    if (item) 
        item->setGeometry({ { x + lw, y }, QSize{ w - lw, th } });
    item = m_items[2];
    if (item)
        item->setGeometry({ { x + lw, y + th }, QSize{ w - lw, h - th } });
}
