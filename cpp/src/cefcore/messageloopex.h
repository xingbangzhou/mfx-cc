#ifndef MESSAGELOOPEX_H
#define MESSAGELOOPEX_H

#include "cefcore/cefmessageloopex.h"

class MessageLoopEx : public CefMessageLoopEx
{
public:
    explicit MessageLoopEx();
    ~MessageLoopEx();

    virtual void setRunner(ExternalRunner runner);
};

#endif // MESSAGELOOPEX_H
