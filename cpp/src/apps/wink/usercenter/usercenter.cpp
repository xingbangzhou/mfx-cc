#include "stable.h"
#include "usercenter.h"

UserCenter::UserCenter(QObject* parent /*= nullptr*/)
    : QObject(parent)
{
    setAvatar(":/resources/usercenter/avatar.jpg");
}

UserCenter::~UserCenter()
{
}

void UserCenter::setAvatar(const QString& value)
{
    m_avatar = value;
    emit avatarChanged(m_avatar);
}

const QString& UserCenter::getAvatar() const
{
    return m_avatar;
}
