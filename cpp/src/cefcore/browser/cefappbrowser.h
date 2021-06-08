#ifndef CEFAPPBROWSER_H
#define CEFAPPBROWSER_H
#include "cefappbase.h"

class CefAppBrowser : public CefAppBase, public CefBrowserProcessHandler
{
public:
    CefAppBrowser();

private:
    void OnBeforeCommandLineProcessing(const CefString& process_type, 
        CefRefPtr<CefCommandLine> command_line) OVERRIDE;
    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE
    {
        return this;
    }

    void OnContextInitialized() OVERRIDE;

    void OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line) OVERRIDE;

    void OnScheduleMessagePumpWork(int64 delay_ms) OVERRIDE;

private:
    IMPLEMENT_REFCOUNTING(CefAppBrowser);
    DISALLOW_COPY_AND_ASSIGN(CefAppBrowser);
};

#endif // CEFAPPBROWSER_H
