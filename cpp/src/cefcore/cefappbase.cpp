#include "stable.h"
#include "cefappbase.h"

const char kProcessType[] = "type";
const char kRendererProcess[] = "renderer";
#if defined(OS_LINUX)
const char kZygoteProcess[] = "zygote";
#endif

CefAppBase::CefAppBase()
{
}

CefAppBase::ProcessType CefAppBase::GetProcessType(CefRefPtr<CefCommandLine> commandLine)
{
    if (!commandLine->HasSwitch(kProcessType))
        return BrowserProcess;

    const std::string& process_type = commandLine->GetSwitchValue(kProcessType);
    if (process_type == kRendererProcess)
        return RendererProcess;
#if defined(OS_LINUX)
    else if (process_type == kZygoteProcess)
        return ZygoteProcess;
#endif

    return OtherProcess;
}

void CefAppBase::OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar)
{
    __super::OnRegisterCustomSchemes(registrar);
}

CefAppOther::CefAppOther()
{
}
