#include "stable.h"
#include "bizitemmodel.h"

#include <QPainter>

/************************************************************************/
/* BizItemDelegate                                                      */
/************************************************************************/
BizItemDelegate::BizItemDelegate(QObject* parent /* = nullptr */)
    : QAbstractItemDelegate(parent)
{
}

void BizItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (!index.isValid())
        return;

    QVariant var = index.data(Qt::UserRole + 1);
    BizItemData itemData = var.value<BizItemData>();
    const QRect& rect = option.rect;

    if (option.state.testFlags(QStyle::State_Selected))
    {
        QImage imageHover;
        imageHover.load(itemData.imageHover);
        int w = imageHover.width();
        int h = imageHover.height();
        painter->drawImage(QPointF{ rect.x() + (rect.width() - w) * 0.5, rect.y() + (rect.height() - h) * 0.5 },
                           imageHover);
    }
    else
    {
        QImage image;
        image.load(itemData.image);
        int w = image.width();
        int h = image.height();
        painter->drawImage(QPointF{ rect.x() + (rect.width() - w) * 0.5, rect.y() + (rect.height() - h) * 0.5 }, image);
    }
}

QSize BizItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    return QSize(20, 20);
}

/************************************************************************/
/* BizItemModel                                                         */
/************************************************************************/
BizItemModel::BizItemModel(QObject* parent /* = nullptr */)
    : QAbstractListModel(parent)
{
}

BizItemModel::~BizItemModel()
{

}

void BizItemModel::setItemList(const QList<BizItemData>& itemList)
{
    beginResetModel();
    m_itemList = itemList;
    endResetModel();
}

void BizItemModel::setActiveIndex(const QModelIndex& index)
{
    clear();
    m_activedIndex = index;
    emit activedChanged(index);
}

QModelIndex BizItemModel::indexById(const QString& id) const
{
    auto itr = std::find_if(
        m_itemList.begin(), m_itemList.end(),
        [this, &id](const BizItemData& value) -> auto { return value.classId == id; });
    return index(itr - m_itemList.begin());
}

int BizItemModel::rowCount(const QModelIndex& parent /*= QModelIndex()*/) const
{
    Q_UNUSED(parent);
    return m_itemList.size();
}

QVariant BizItemModel::data(const QModelIndex& index, int role /*= Qt::DisplayRole*/) const
{
    Q_UNUSED(role);
    if (m_itemList.isEmpty())
        return QVariant();
    BizItemData data = m_itemList.value(index.row());
    return QVariant::fromValue(data);
}

void BizItemModel::clear()
{
    m_activedIndex = QModelIndex();
}
