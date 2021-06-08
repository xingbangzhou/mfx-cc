#ifndef CEFSGLOOP_H
#define CEFSGLOOP_H
#include "qcompilerdetection.h"
#include <functional>

class CefMsgLoopHelp
{
public:
    typedef std::function<void()> MspLoopRunner;
    void setRunner(MspLoopRunner runner){};

protected:
    explicit CefMsgLoopHelp() Q_DECL_EQ_DEFAULT;
    ~CefMsgLoopHelp() Q_DECL_EQ_DEFAULT;
};

#endif
