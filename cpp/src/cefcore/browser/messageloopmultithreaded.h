#ifndef MESSAGELOOPMULTITHREADED_H
#define MESSAGELOOPMULTITHREADED_H
#include "messageloop.h"
#include "qcompilerdetection.h"

class MessageLoopMultiThread : public MessageLoop
{
public:
    MessageLoopMultiThread();
    ~MessageLoopMultiThread();

    int run() Q_DECL_OVERRIDE;

    void quit() Q_DECL_OVERRIDE;

    void postTask(CefRefPtr<CefTask> task) Q_DECL_OVERRIDE;

    bool runsTasksOnCurrentThread() const Q_DECL_OVERRIDE;
};

#endif // MESSAGELOOPMULTITHREADED_H
