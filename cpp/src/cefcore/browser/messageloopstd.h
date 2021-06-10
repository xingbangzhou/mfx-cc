#ifndef MESSAGELOOPSTD_H
#define MESSAGELOOPSTD_H
#include "messageloop.h"
#include "qcompilerdetection.h"

class MessageLoopStd : public MessageLoop
{
public:
    MessageLoopStd();
    ~MessageLoopStd();

    int run() Q_DECL_OVERRIDE;

    void quit() Q_DECL_OVERRIDE;

    void postTask(CefRefPtr<CefTask> task) Q_DECL_OVERRIDE;

    bool runsTasksOnCurrentThread() const Q_DECL_OVERRIDE;
};

#endif
