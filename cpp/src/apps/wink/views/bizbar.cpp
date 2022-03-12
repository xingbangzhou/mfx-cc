#include "stable.h"

#include <QStyleOption>
#include <QPainter>
#include <QListView>
#include <QVBoxLayout>
#include <QPaintEvent>

#include "bizbar.h"
#include "bizcenter.h"

/************************************************************************/
/* Avatar                                                               */
/************************************************************************/
Avatar::Avatar(QWidget* parent /* = nullptr */)
    : QWidget(parent)
{
    setImage(":/resources/bizcenter/avatar.jpg");
}

Avatar::~Avatar()
{

}

const QString& Avatar::getImage() const
{
    return m_image;
}

void Avatar::setImage(const QString& image)
{
    m_image = image;
    m_imageDevice.load(m_image);
    emit imageChanged(m_image);
}

void Avatar::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    const QRect &rect = event->rect();
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawImage(rect, m_imageDevice);
}

/************************************************************************/
/* BizBar                                                               */
/************************************************************************/
BizBar::BizBar(QWidget* parent) 
    : QWidget(parent)
    , m_avatar(new Avatar(this))
    , m_listView(new QListView(this))
{
    setObjectName("BizBar");
    
    m_listView->setModel(new BizCenter(this));
    m_listView->setItemDelegate(new BizItemDelegate(this));

    QVBoxLayout* layout = new QVBoxLayout(this);
    m_avatar->setFixedSize({40, 40});
    layout->addWidget(m_avatar);
    layout->addSpacing(20);
    layout->addWidget(m_listView);
    setLayout(layout);
}

BizBar::~BizBar()
{

}

void BizBar::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QStyleOption styleOpt;
    styleOpt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}
