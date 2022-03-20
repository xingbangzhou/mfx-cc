#include "stable.h"

#include <QStyleOption>
#include <QPainter>
#include <QListView>
#include <QVBoxLayout>
#include <QPaintEvent>

#include "leftbar.h"
#include "wkframework.h"
#include "bizcenter.h"
#include "bizitemmodel.h"
#include "usercenter.h"

/************************************************************************/
/* Avatar                                                               */
/************************************************************************/
Avatar::Avatar(QWidget* parent /* = nullptr */)
    : QWidget(parent)
{

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

void Avatar::mousePressEvent(QMouseEvent* event)
{
    QWidget::mousePressEvent(event);
}

/************************************************************************/
/* LeftBar                                                              */
/************************************************************************/
LeftBar::LeftBar(QWidget* parent) 
    : QWidget(parent)
    , m_avatar(new Avatar(this))
    , m_listView(new QListView(this))
{
    setObjectName("LeftBar");
    // Layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    m_avatar->setFixedSize({40, 40});
    layout->addWidget(m_avatar);
    layout->addSpacing(20);
    layout->addWidget(m_listView);
    setLayout(layout);

    // Bind BizCenter
    auto bizModel = wkApp->bizCenter()->model();
    m_listView->setModel(bizModel);
    m_listView->setItemDelegate(new BizItemDelegate(this));
    connect(m_listView, &QListView::clicked, this, &LeftBar::onItemclicked);
    connect(bizModel, &BizItemModel::activedChanged, this, &LeftBar::onActivedChanged);

    // Bind UserCenter
    auto userCenter = wkApp->userCenter();
    connect(userCenter, &UserCenter::avatarChanged, m_avatar, &Avatar::setImage);
    m_avatar->setImage(userCenter->getAvatar());
}

LeftBar::~LeftBar()
{

}

Avatar* LeftBar::avatar() const
{
    return m_avatar;
}

void LeftBar::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QStyleOption styleOpt;
    styleOpt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}

void LeftBar::onItemclicked(const QModelIndex& index)
{
    wkApp->bizCenter()->model()->setActiveIndex(index);
}

void LeftBar::onActivedChanged(const QModelIndex& index)
{
    m_listView->setCurrentIndex(index);
}
