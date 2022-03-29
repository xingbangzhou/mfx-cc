#include "stable.h"
#include "mp4player.h"
#include "mp4view.h"
#include "wkframework.h"

IMPLEMENT_XHREFLECT(MP4Player)

MP4Player::MP4Player(QObject* parent)
    : BizRealizable(parent)
    , m_view(nullptr)
{
    
}

MP4Player::~MP4Player()
{
}

void MP4Player::activate()
{
    wkLogger->info("MP4Player::activate");
}

void MP4Player::inactivate()
{
    wkLogger->info("MP4Player::inactivate");
}

QWidget* MP4Player::widget()
{
    if (nullptr == m_view)
    {
        m_view = new MP4View();
    }
    return m_view;
}
