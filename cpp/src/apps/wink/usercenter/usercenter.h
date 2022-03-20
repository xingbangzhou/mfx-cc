#ifndef USERCENTER_H
#define USERCENTER_H

#include <QObject>

class UserCenter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString avatar READ getAvatar WRITE setAvatar NOTIFY avatarChanged)
public:
    explicit UserCenter(QObject* parent = nullptr);
    ~UserCenter();

    void setAvatar(const QString& value); 
    const QString& getAvatar() const;

signals:
    void avatarChanged(const QString& avatar);

private:
    QString m_avatar;
};

#endif // USERCENTER_H
