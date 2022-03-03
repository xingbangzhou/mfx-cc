#include "stable.h"
#include "titlebar.h"

#include <QCoreApplication>
#include <QPushButton>
#include <algorithm>
#include <iterator>
#include "QBoxLayout"

TitleBar::TitleBar(QWidget* parent /* = nullptr */) : QWidget(parent)
{
    QPalette palette(this->palette());
    palette.setColor(QPalette::Window, QColor(204, 213, 240));
    setAutoFillBackground(true);
    setPalette(palette);

    m_minizeBtn = new QPushButton(this);
    m_minizeBtn->setObjectName("MinizeButton");
    m_minizeBtn->setText("minimize");
    connect(m_minizeBtn, SIGNAL(clicked(bool)), this, SLOT(minized()));
    m_minmaxBtn = new QPushButton(this);
    m_minmaxBtn->setObjectName("MinmaxButton");
    m_minmaxBtn->setText("minmax");
    connect(m_minmaxBtn, SIGNAL(clicked(bool)), this, SLOT(minmaxed()));
    m_closeBtn = new QPushButton(this);
    m_closeBtn->setObjectName("CloseButton");
    m_closeBtn->setText("close");
    connect(m_closeBtn, SIGNAL(clicked(bool)), this, SLOT(closed()));

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addStretch(1);
    layout->addWidget(m_minizeBtn);
    layout->addWidget(m_minmaxBtn);
    layout->addWidget(m_closeBtn);
    setLayout(layout);
}

TitleBar::~TitleBar()
{

}

void TitleBar::getBtns(QList<QWidget*>& out) const
{
    out.append(m_closeBtn);
    out.append(m_minmaxBtn);
    out.append(m_minizeBtn);
}

void TitleBar::closed()
{
    qApp->quit();
}

void TitleBar::minmaxed()
{
    auto topWidget = parentWidget()->parentWidget();
    auto flag = topWidget->isMaximized();
    flag ? topWidget->showNormal() : topWidget->showMaximized();
}

void TitleBar::minized()
{
    parentWidget()->parentWidget()->showMinimized();
}
