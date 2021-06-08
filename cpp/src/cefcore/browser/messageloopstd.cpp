#include "stable.h"
#include "messageloopstd.h"
#include "include/cef_app.h"

MessageLoopStd::MessageLoopStd()
{
}

MessageLoopStd::~MessageLoopStd()
{
}

int MessageLoopStd::run()
{
    CefRunMessageLoop();
    return 0;
}

void MessageLoopStd::quit()
{
    CefQuitMessageLoop();
}
