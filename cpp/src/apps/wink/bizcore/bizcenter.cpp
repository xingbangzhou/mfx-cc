#include "stable.h"
#include "bizcenter.h"

BizCenter::BizCenter(QObject* parent /*= nullptr*/)
     : QAbstractListModel(parent)
{
    m_itemList.push_back(
        { "MP4ActiveView", u8"MP4动效", ":/resources/bizcenter/mp4.png", ":/resources/bizcenter/mp4_hover.png" });
}

BizCenter::~BizCenter()
{
}

int BizCenter::rowCount(const QModelIndex& parent /*= QModelIndex()*/) const
{
    Q_UNUSED(parent);
    return m_itemList.size();
}

QVariant BizCenter::data(const QModelIndex& index, int role /*= Qt::DisplayRole*/) const
{
    Q_UNUSED(role);
    if (m_itemList.isEmpty())
        return QVariant();
    BizItemData data = m_itemList.value(index.row());
    return QVariant::fromValue(data);
}

void BizCenter::clearActived()
{
    m_activedId.clear();
}

void BizCenter::setActiveId(const QString& id)
{
    m_activedId = id;

    auto curIndex = activedIndex();
    emit activedChanged(curIndex);
}

void BizCenter::setActiveIndex(const QModelIndex& index)
{
    clearActived();
    if (index.isValid())
    {
        m_activedId = index.data().value<BizItemData>().classId;
    }
    emit activedChanged(index);
}

const QString& BizCenter::activedId() const
{
    return m_activedId;
}

QModelIndex BizCenter::activedIndex() const
{
    auto itr = std::find_if(m_itemList.begin(), m_itemList.end(), [this](const BizItemData& value) -> auto { 
        return value.classId == m_activedId;
    });
    return index(itr - m_itemList.begin());
}
