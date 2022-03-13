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

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

private slots:
    void onCurrentChanged(const QModelIndex& current);

private:
    QVector<BizItemData> m_vctItems;
};

#endif // BIZCENTER_H
