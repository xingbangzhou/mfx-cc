#ifndef MESSAGELOOPMULTITHREADED_H
#define MESSAGELOOPMULTITHREADED_H
#include "cefcore/cefmessageloop.h"
#include "qcompilerdetection.h"

class MessageLoopMultiThread : public CefMessageLoop
{
public:
    MessageLoopMultiThread();
    ~MessageLoopMultiThread();

    int run() Q_DECL_OVERRIDE;
    void quit() Q_DECL_OVERRIDE;
};

#endif
