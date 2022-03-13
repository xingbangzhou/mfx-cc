#ifndef BIZCENTER_H
#define BIZCENTER_H

#include "bizitem.h"

#include <QAbstractListModel>

class BizCenter : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit BizCenter(QObject* parent = nullptr);
    ~BizCenter();

    void setActiveId(const QString& id);
    void setActiveIndex(const QModelIndex& index);
    
    const QString& activedId() const;

    QModelIndex activedIndex() const;

    // QAbstractListModel
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

signals:
    void activedChanged(const QModelIndex& index);

private:
    void clearActived();

private:
    QList<BizItemData> m_itemList;
    QString m_activedId;
};

#endif // BIZCENTER_H
