#ifndef BIZCENTER_H
#define BIZCENTER_H

#include <QObject>

class BizItemModel;
class BizCenter : public QObject
{
    Q_OBJECT
public:
    explicit BizCenter(QObject* parent = nullptr);
    ~BizCenter();

    void setActiveId(const QString& id);

    BizItemModel* model() const;

private:
    BizItemModel* m_model;
};

#endif // BIZCENTER_H
