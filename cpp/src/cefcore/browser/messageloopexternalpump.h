#ifndef MESSAGELOOPEXTERNALPUMP_H
#define MESSAGELOOPEXTERNALPUMP_H
#include "cefcore/cefmessageloop.h"
#include "qcompilerdetection.h"
#include "include/base/cef_basictypes.h"

class MessageLoopExternalPump : public CefMessageLoop
{
public:
    MessageLoopExternalPump();
    ~MessageLoopExternalPump();

    int run() Q_DECL_OVERRIDE;
    void quit() Q_DECL_OVERRIDE;

    void setRunner(MessageLoopRunner runner)
    {
        m_runner = runner;
    };

    void OnScheduleMessagePumpWork(int64 delay_ms);
    
private:
    MessageLoopRunner m_runner;
};

#endif
