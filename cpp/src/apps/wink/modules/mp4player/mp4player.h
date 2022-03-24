#ifndef MP4PLAYER_H
#define MP4PLAYER_H

#include "xhcore/xhreflect.h"

class MP4Player : public QObject
{
    Q_OBJECT
    DECLARE_XHREFLECT(MP4Player, "mp4player")
public:
    explicit MP4Player(QObject* parent = nullptr);
    ~MP4Player();
};

#endif // MP4PLAYER_H
