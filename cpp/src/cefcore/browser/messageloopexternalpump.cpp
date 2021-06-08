#include "stable.h"
#include "messageloopexternalpump.h"

#ifdef Q_OS_WIN
#include <winuser.h>
#endif // Q_OS_WIN

MessageLoopExternalPump::MessageLoopExternalPump()
{
}

MessageLoopExternalPump::~MessageLoopExternalPump()
{
}

int MessageLoopExternalPump::run()
{
    if (m_runner)
    {
        m_runner();
    }
}

void MessageLoopExternalPump::quit()
{
#ifdef Q_OS_WIN
    PostMessage(NULL, WM_QUIT, 0, 0);
#endif // Q_OS_WIN
}

void MessageLoopExternalPump::OnScheduleMessagePumpWork(int64 delay_ms)
{
}
