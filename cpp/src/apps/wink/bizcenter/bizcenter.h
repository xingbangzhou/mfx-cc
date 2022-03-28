#ifndef BIZCENTER_H
#define BIZCENTER_H

#include <QObject>

class BizItemModel;
class BizCenterPrivate;
class BizCenter : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(BizCenter)
public:
    explicit BizCenter(QObject* parent = nullptr);
    ~BizCenter();

    void init();

    void setActiveId(const QString& cid);

    BizItemModel* model() const;

private:
    BizCenterPrivate* d_ptr;
    BizItemModel* m_model;
};

#endif // BIZCENTER_H
