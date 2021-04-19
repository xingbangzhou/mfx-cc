#include "stable.h"
#include "cefcore/cefframework.h"
#include "include/cef_app.h"

CefFramework* CefFramework::self = nullptr;

CefFramework::CefFramework()
{
    self = this;
}

CefFramework::~CefFramework()
{

}

void CefFramework::appendCmd(const QString& name, const QString& value)
{
    m_cmdExtras.push_back(qMakePair(name, value));
}

bool CefFramework::init(int argc, const char* const* argv)
{
    CefEnableHighDPISupport();
    m_cmdLine = CefCommandLine::CreateCommandLine();
    m_cmdLine->InitFromArgv(argc, argv);
    for 
        each(auto var in m_cmdExtras)
        {
            m_cmdLine->AppendSwitchWithValue(var.first, var.second);
        }
    return true;
}

void CefFramework::uninit()
{

}
