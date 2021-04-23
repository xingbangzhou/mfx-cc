#include "stable.h"
#include "cefframework_p.h"
#include "include/cef_app.h"
#include "cefappbase.h"
#include "browser/cefappbrowser.h"

CefFrameworkPrivate::CefFrameworkPrivate() 
    : initialized(false)
{
}

CefFrameworkPrivate::~CefFrameworkPrivate()
{
}

bool CefFrameworkPrivate::initEnv(int argc, const char* const* argv)
{
    DCHECK(!initialized);
    Q_Q(CefFramework);
    commandLine = CefCommandLine::CreateCommandLine();
    commandLine->InitFromArgv(argc, argv);
    for (auto item : switchList)
    {
        commandLine->AppendSwitchWithValue(item.first.toStdString(), item.second.toStdString());
    }
    HINSTANCE hInstance = GetModuleHandle(NULL);
    CefMainArgs mainArgs(hInstance);
    
    CefAppBase::ProcessType processType = CefAppBase::GetProcessType(commandLine);
    if (processType == CefAppBase::BrowserProcess)
    {
        app = new CefAppBrowser();
    }

    int exitCode = CefExecuteProcess(mainArgs, app, nullptr);
    if (exitCode >= 0)
    {
        return false;
    }

    CefSettings settings;
    settings.background_color = q->backgroundColor();
    settings.windowless_rendering_enabled = true;
    settings.ignore_certificate_errors = false;
    settings.no_sandbox = true;
    settings.multi_threaded_message_loop = false;
    settings.external_message_pump = q->m_msgLoop ? true : false;

    if (CefInitialize(mainArgs, settings, app, nullptr))
    {
        return false;
    }
    
    initialized = true;

    return true;
}

void CefFrameworkPrivate::uninitEnv()
{
    DCHECK(initialized);
    CefShutdown();
    initialized = false;
}
