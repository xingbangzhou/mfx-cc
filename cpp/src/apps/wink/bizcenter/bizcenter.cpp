#include "stable.h"
#include "bizcenter.h"
#include "bizitemmodel.h"
#include "xhcore/xhreflect.h"

/*
* BizFactory
*/
class BizCenterPrivate
{
    Q_DECLARE_PUBLIC(BizCenter)
public:
    BizCenterPrivate(BizCenter* q)
        : q_ptr(q)
    {
    }

private:
    BizCenter* q_ptr;
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

void BizCenter::setActiveId(const QString& id)
{
    Q_UNUSED(id);
}

BizItemModel* BizCenter::model() const
{
    return m_model;
}
