#include "stable.h"
#include "cefcore/cefframework.h"
#include "include/cef_app.h"
#include "cefframework_p.h"

CefFramework* CefFramework::self = nullptr;

CefFramework::CefFramework() 
    : d_ptr(new CefFrameworkPrivate)
{
    Q_D(CefFramework);
    d->q_ptr = this;

    Q_ASSERT_X(!self, "CefFramework", "there should be only one framework object");
    CefFramework::self = this;
}

CefFramework::~CefFramework()
{
    Q_D(CefFramework);
    d->shutdown();
}

void CefFramework::setSwitchFlag(SwitchFlag flag, bool on /*= true*/)
{
    Q_D(CefFramework);
    if (on)
    {
        d->switchFlags |= 1 << flag;
    }
    else
    {
        d->switchFlags &= ~(1 << flag);
    }
}

bool CefFramework::testSwitchFlag(SwitchFlag flag)
{
    Q_D(CefFramework);
    return d->switchFlags & (1 << flag);
}

void CefFramework::setOsrFrameRate(int rate)
{
    Q_D(CefFramework);
    d->osrFrameRate = rate;
}

void CefFramework::enableTransparentPrinting(bool enable /*= true*/)
{
    Q_D(CefFramework);
    d->transparentPrintingEnabled = enable;
}

#if defined(Q_OS_WIN)
void CefFramework::enableSharedTexture(bool enable /*= true*/)
{
    Q_D(CefFramework);
    d->sharedTextureEnabled = enable;
}
#endif

void CefFramework::enableExternalBeginFrame(bool enable /*= true*/)
{
    Q_D(CefFramework);
    d->externalBeginFrameEnabled = enable;
}

void CefFramework::setCachePath(const std::string& path)
{
    Q_D(CefFramework);
    d->cachePath = path;
}

const std::string& CefFramework::cachePath()
{
    Q_D(CefFramework);
    return d->cachePath;
}

void CefFramework::setBackgroundColor(const QColor& color)
{
    Q_D(CefFramework);
    d->backgroundColor = color;
}

const QColor& CefFramework::backgroundColor()
{
    Q_D(CefFramework);
    return d->backgroundColor;
}

bool CefFramework::initialize(int argc, const char* const* argv)
{
    Q_D(CefFramework);
    return d->initialize(argc, argv);
}

int CefFramework::run()
{
    Q_D(CefFramework);
    // TODO: Init RootWindow

    return d->messageLoop->run();
}
