#include "stable.h"
#include "cefappbrowser.h"

CefAppBrowser::CefAppBrowser()
{

}

void CefAppBrowser::OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line)
{
}

void CefAppBrowser::OnContextInitialized()
{
}

void CefAppBrowser::OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line)
{
}

void CefAppBrowser::OnScheduleMessagePumpWork(int64 delay_ms)
{
}
