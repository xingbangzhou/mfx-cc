#include "stable.h"
#include "mp4player.h"

#include <QDebug>

IMPLEMENT_XHREFLECT(MP4Player)

MP4Player::MP4Player(QObject* parent) : QObject(parent)
{
    qDebug() << "--------------MP4Player()";
}

MP4Player::~MP4Player()
{
}
