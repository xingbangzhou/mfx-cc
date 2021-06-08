#include "stable.h"
#include "cefframework_p.h"
#include "include/cef_app.h"
#include "cefappbase.h"
#include "browser/cefappbrowser.h"
#include "switches.h"
#include "render/cefapprender.h"
#include "browser/messageloopmultithreaded.h"
#include "browser/messageloopexternalpump.h"
#include "browser/messageloopstd.h"

CefFrameworkPrivate::CefFrameworkPrivate() 
    : switchFlags(0)
    , osrFrameRate(0)
    , transparentPrintingEnabled(false)
    , externalBeginFrameEnabled(false)
#if defined(Q_OS_WIN)
    , sharedTextureEnabled(false)
#endif
{
}

CefFrameworkPrivate::~CefFrameworkPrivate()
{
}

bool CefFrameworkPrivate::initialize(int argc, const char* const* argv)
{
    Q_ASSERT(!m_initialized);
    Q_ASSERT(!m_shutdown);

    Q_Q(CefFramework);
    
    commandLine = CefCommandLine::CreateCommandLine();
    commandLine->InitFromArgv(argc, argv);

    HINSTANCE hInstance = GetModuleHandle(NULL);
    CefMainArgs mainArgs(hInstance);

    _createApp();
    
    int exitCode = CefExecuteProcess(mainArgs, app, nullptr);
    if (exitCode >= 0)
    {
        return false;
    }

    CefSettings settings;
    _populateSettings(&settings);
    _createMessageLoop(&settings);

    if (!CefInitialize(mainArgs, settings, app, nullptr))
    {
        return false;
    }

    m_initialized = true;

    return true;
}

void CefFrameworkPrivate::shutdown()
{
    Q_ASSERT(m_initialized);
    Q_ASSERT(!m_shutdown);

    CefShutdown();
    messageLoop.reset();
    
    m_shutdown = true;
}

void CefFrameworkPrivate::_createApp()
{
    Q_ASSERT(!app);

    CefAppBase::ProcessType processType = CefAppBase::GetProcessType(commandLine);
    if (processType == CefAppBase::BrowserProcess)
    {
        app = new CefAppBrowser();
    }
    else if (processType == CefAppBase::RendererProcess)
    {
        app = new CefAppRender();
    }
    else
    {
        app = new CefAppOther();
    }
}

void CefFrameworkPrivate::_populateSettings(CefSettings* settings)
{
    Q_Q(CefFramework);

    // 缓存
    if (cachePath.empty())
    {
        cachePath = commandLine->GetSwitchValue(switches::kCachePath);
    }
    CefString(&settings->cache_path) = cachePath;
    // 离屏
    bool osrRenderingEnabled = q->testSwitchFlag(CefFramework::OsrRenderingEnabled);
    if (osrRenderingEnabled)
    {
        settings->windowless_rendering_enabled = true;
    }
    // 背景色
    if (!backgroundColor.isValid())
    {
        backgroundColor = QColor(255, 255, 255, 255);
    }
    settings->background_color = CefColorSetARGB(backgroundColor.alpha(), backgroundColor.red(),
                                                 backgroundColor.green(), backgroundColor.blue());
// 事件循环方式
#if (defined(OS_WIN) || defined(OS_LINUX))
    settings->multi_threaded_message_loop = q->testSwitchFlag(CefFramework::MultiThreadedMessageLoop)
                                            || commandLine->HasSwitch(switches::kMultiThreadedMessageLoop);
#endif

    if (!settings->multi_threaded_message_loop)
    {
        settings->external_message_pump = q->testSwitchFlag(CefFramework::ExternalMessagePump)
                                          || commandLine->HasSwitch(switches::kExternalMessagePump);
    }
}

void CefFrameworkPrivate::_createMessageLoop(const CefSettings* const settings)
{
    if (settings->multi_threaded_message_loop) {
        messageLoop.reset(new MessageLoopMultiThread());
    }
    else if (settings->external_message_pump)
    {
        messageLoop.reset(new MessageLoopExternalPump());
    }
    else
    {
        messageLoop.reset(new MessageLoopStd());
    }
}
