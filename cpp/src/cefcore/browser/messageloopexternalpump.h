#ifndef MESSAGELOOPEXTERNALPUMP_H
#define MESSAGELOOPEXTERNALPUMP_H
#include "messageloopstd.h"
#include "qcompilerdetection.h"
#include "include/base/cef_basictypes.h"
#include "cefcore/cefmessageloopex.h"

class MessageLoopExternalPump : public MessageLoopStd
{
public:
    explicit MessageLoopExternalPump();
    virtual ~MessageLoopExternalPump();

    int run() Q_DECL_OVERRIDE;

    void quit() Q_DECL_OVERRIDE;

    void setRunner(CefMessageLoopEx::ExternalRunner runner)
    {
        m_runner = runner;
    };

    void OnScheduleMessagePumpWork(int64 delay_ms);
    
private:
    CefMessageLoopEx::ExternalRunner m_runner;
};

#endif // MESSAGELOOPEXTERNALPUMP_H
