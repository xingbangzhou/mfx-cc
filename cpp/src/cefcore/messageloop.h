#ifndef MESSAGELOOP_H
#define MESSAGELOOP_H

#include "qcompilerdetection.h"
#include "include/cef_task.h"

class MessageLoop
{
public:
    virtual ~MessageLoop() {};

    virtual int run() = 0;
    virtual void quit() = 0;

    // Post a task for execution on the main message loop.
    virtual void postTask(CefRefPtr<CefTask> task) = 0;

    // Returns true if this message loop runs tasks on the current thread.
    virtual bool runsTasksOnCurrentThread() const = 0;

protected:
    explicit MessageLoop() Q_DECL_EQ_DEFAULT;
};

#endif // MESSAGELOOP_H
