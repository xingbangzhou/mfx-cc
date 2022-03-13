#include "stable.h"
#include "bizcenter.h"

BizCenter::BizCenter(QObject* parent /*= nullptr*/)
     : QAbstractListModel(parent)
{
    m_vctItems.push_back(
        { "MP4ActiveView", u8"MP4动效", ":/resources/bizcenter/mp4.png", ":/resources/bizcenter/mp4_hover.png" });
}

BizCenter::~BizCenter()
{
}

int BizCenter::rowCount(const QModelIndex& parent /*= QModelIndex()*/) const
{
    Q_UNUSED(parent);
    return m_vctItems.size();
}

QVariant BizCenter::data(const QModelIndex& index, int role /*= Qt::DisplayRole*/) const
{
    Q_UNUSED(role);
    if (m_vctItems.isEmpty())
        return QVariant();
    BizItemData data = m_vctItems.value(index.row());
    return QVariant::fromValue(data);
}

void BizCenter::onCurrentChanged(const QModelIndex& current)
{
}
