#include "stable.h"
#include "cefcore/cefframework.h"
#include "include/cef_app.h"
#include "cefframework_p.h"

CefFramework* CefFramework::self = nullptr;

CefFramework::CefFramework() : d_ptr(new CefFrameworkPrivate)
{
    Q_D(CefFramework);
    d->q_ptr = this;
    self = this;
}

CefFramework::~CefFramework()
{

}

void CefFramework::appendSwtich(const QString& name, const QString& value)
{
    Q_D(CefFramework);
    d->switchList.push_back(qMakePair(name, value));
}

int CefFramework::init(int argc, const char* const* argv)
{
    Q_D(CefFramework);
    return d->initEnv(argc, argv);
}

void CefFramework::uninit()
{
    
}
