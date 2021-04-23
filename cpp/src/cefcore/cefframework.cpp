#include "stable.h"
#include "cefcore/cefframework.h"
#include "include/cef_app.h"
#include "cefframework_p.h"

CefFramework* CefFramework::self = nullptr;

CefFramework::CefFramework() 
    : d_ptr(new CefFrameworkPrivate)
    , m_backgroundColor(0)
{
    Q_D(CefFramework);
    d->q_ptr = this;

    Q_ASSERT_X(!self, "CefFramework", "there should be only one application object");
    CefFramework::self = this;
}

CefFramework::~CefFramework()
{
    Q_D(CefFramework);
    d->uninitEnv();
}

void CefFramework::setBackgroundColor(unsigned int value)
{
    m_backgroundColor = value;
}

unsigned int CefFramework::backgroundColor() const
{
    return m_backgroundColor;
}

void CefFramework::setMsgLoop(MessageLoop loop)
{
    m_msgLoop = loop;
}

void CefFramework::appendSwtich(const QString& name, const QString& value)
{
    Q_D(CefFramework);
    d->switchList.push_back(qMakePair(name, value));
}

bool CefFramework::init(int argc, const char* const* argv)
{
    Q_D(CefFramework);
    return d->initEnv(argc, argv);
}

int CefFramework::exec()
{
    if (m_msgLoop)
    {
       return m_msgLoop();
    }
    
    CefRunMessageLoop();
    return 0;
}
