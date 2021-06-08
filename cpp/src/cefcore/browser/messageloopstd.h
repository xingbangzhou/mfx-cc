#ifndef MESSAGELOOPSTD_H
#define MESSAGELOOPSTD_H
#include "cefcore/cefmessageloop.h"
#include "qcompilerdetection.h"

class MessageLoopStd : public CefMessageLoop
{
public:
    MessageLoopStd();
    ~MessageLoopStd();

    int run() Q_DECL_OVERRIDE;
    void quit() Q_DECL_OVERRIDE;
};

#endif
