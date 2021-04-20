#include "stable.h"
#include "cefframework_p.h"
#include "include/cef_app.h"
#include "cefappbase.h"

 CefFrameworkPrivate::CefFrameworkPrivate()
{
}

CefFrameworkPrivate::~CefFrameworkPrivate()
{
}

int CefFrameworkPrivate::initEnv(int argc, const char* const* argv)
{
    commandLine = CefCommandLine::CreateCommandLine();
    commandLine->InitFromArgv(argc, argv);
    for (auto item : switchList)
    {
        commandLine->AppendSwitchWithValue(item.first.toStdString(), item.second.toStdString());
    }
    HINSTANCE hInstance = GetModuleHandle(NULL);
    CefMainArgs mainArgs(hInstance);

    CefRefPtr<CefApp> app;
    CefAppBase::ProcessType processType = CefAppBase::GetProcessType(commandLine);

    int exitCode = CefExecuteProcess(mainArgs, app, nullptr);
    if (exitCode >= 0)
    {
        return exitCode;
    }



    return exitCode;
}

void CefFrameworkPrivate::uninitEnv()
{
}
