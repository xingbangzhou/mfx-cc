#ifndef MP4PLAYER_H
#define MP4PLAYER_H

#include "xhcore/xhreflect.h"
#include "bizrealizable.h"

class MP4View;
class MP4Player : public BizRealizable
{
    Q_OBJECT
    DECLARE_XHREFLECT(MP4Player, "mp4player")
public:
    explicit MP4Player(QObject* parent = nullptr);
    ~MP4Player();

protected:
    // BizRealizable
    void activate() override;
    void inactivate() override;
    QWidget* widget() override;

private:
    MP4View* m_view;
};

#endif // MP4PLAYER_H
