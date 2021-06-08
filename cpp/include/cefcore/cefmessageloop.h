#ifndef CEFMESSAGELOOP_H
#define CEFMESSAGELOOP_H
#include "qcompilerdetection.h"

class CefMessageLoop
{
public:
    virtual int run() = 0;
    virtual void quit() = 0;

protected:
    explicit CefMessageLoop() Q_DECL_EQ_DEFAULT;
    virtual ~CefMessageLoop() Q_DECL_EQ_DEFAULT;
};

#endif
