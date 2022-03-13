#include "stable.h"
#include "bizitem.h"

#include <QPainter>

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
