#ifndef CEFAPPBASE_H
#define CEFAPPBASE_H
#include "include/cef_app.h"

class CefAppBase : public CefApp
{
public:
    CefAppBase();

    enum ProcessType
    {
        BrowserProcess,
        RendererProcess,
        ZygoteProcess,
        OtherProcess
    };

    static ProcessType GetProcessType(CefRefPtr<CefCommandLine> commandLine);

private:
    DISALLOW_COPY_AND_ASSIGN(CefAppBase);
    
    void OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) OVERRIDE;
};

class CefAppOther : public CefAppBase
{
public:
    CefAppOther();

private:
    IMPLEMENT_REFCOUNTING(CefAppOther);
    DISALLOW_COPY_AND_ASSIGN(CefAppOther);
};

#endif // CEFBASEAPP_H
