#ifndef BIZITEMMODEL_H
#define BIZITEMMODEL_H

#include <QAbstractItemDelegate>
#include <QAbstractListModel>
#include <QList>

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

class BizItemModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit BizItemModel(QObject* parent = nullptr);
    ~BizItemModel();

    void setActiveIndex(const QModelIndex& index);

    QModelIndex indexById(const QString& id) const;

    // QAbstractListModel
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

signals:
    void activedChanged(const QModelIndex& index);

private:
    void clear();

private:
    QList<BizItemData> m_itemList;
    QModelIndex m_activedIndex;
};

Q_DECLARE_METATYPE(BizItemData);

#endif //BIZITEMMODEL_H
