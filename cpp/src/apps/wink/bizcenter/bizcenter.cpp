#include "stable.h"

#include <map>

#include "bizcenter.h"
#include "bizitemmodel.h"
#include "bizrealizable.h"
#include "xhcore/xhreflect.h"
#include "frameview.h"
#include "wkframework.h"

/*
* BizCenterPrivate
*/
class BizCenterPrivate
{
    Q_DECLARE_PUBLIC(BizCenter)
public:
    BizCenterPrivate(BizCenter* q)
        : q_ptr(q)
    {
    }

    BizRealizable* getBizObject(const QString& cid)
    {
        auto itr = m_mapBizObj.lower_bound(cid);
        if (itr == m_mapBizObj.end() || !m_mapBizObj.key_comp()(itr->first, cid))
        {
            BizRealizable* obj = reinterpret_cast<BizRealizable*>(xh_createObject(cid));
            m_mapBizObj.insert(itr, { cid, obj });
            return obj;
        }
        return itr->second;
    }

private:
    BizCenter* q_ptr;
    std::map<QString, BizRealizable*> m_mapBizObj;
};

/*
* BizCenter
*/
BizCenter::BizCenter(QObject* parent /*= nullptr*/)
    : QObject(parent)
    , d_ptr(new BizCenterPrivate(this))
    , m_model(new BizItemModel(this))
{
    
}

BizCenter::~BizCenter()
{
}

void BizCenter::init()
{
    QList<BizItemData> itemList;
    itemList.push_back({ "mp4player", u8"MP4特效", ":/resources/bizcenter/mp4.png", ":/resources/bizcenter/mp4_hover.png"});
    m_model->setItemList(itemList);
}

void BizCenter::setActiveId(const QString& cid)
{
    Q_D(BizCenter);
    BizRealizable* pObj = d->getBizObject(cid);
    wkApp->frameView()->setView(pObj->widget());
    pObj->activate();
}

BizItemModel* BizCenter::model() const
{
    return m_model;
}
