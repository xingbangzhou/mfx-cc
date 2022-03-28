#ifndef BIZREALIZABLE_H
#define BIZREALIZABLE_H

#include <QObject>

class QWidget;
class BizRealizable : public QObject
{
    Q_OBJECT
public:
    explicit BizRealizable(QObject* parent = nullptr);
    ~BizRealizable();

    virtual void activate() = 0;
    virtual void inactivate() = 0;
    virtual QWidget* widget() = 0;
};

#endif // BIZREALIZABLE_H
