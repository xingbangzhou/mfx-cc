#ifndef BIZITEM_H
#define BIZITEM_H

#include <QAbstractItemDelegate>

struct BizItemData
{
    QString classId;
    QString tipText;
    QString image;
    QString imageHover;
};

class BizItemDelegate : public QAbstractItemDelegate
{
    Q_OBJECT

public:
    explicit BizItemDelegate(QObject* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

Q_DECLARE_METATYPE(BizItemData);

#endif
