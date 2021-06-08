#include "stable.h"
#include "cefappbrowser.h"
#include "switches.h"

CefAppBrowser::CefAppBrowser()
{

}

void CefAppBrowser::OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line)
{
    if (process_type.empty())
    {
        // Pass additional command-line flags when off-screen rendering is enabled.
        if (command_line->HasSwitch(switches::kOffScreenRenderingEnabled)
            && !command_line->HasSwitch(switches::kSharedTextureEnabled))
        {
            // Use software rendering and compositing (disable GPU) for increased FPS
            // and decreased CPU usage. This will also disable WebGL so remove these
            // switches if you need that capability.
            // See https://bitbucket.org/chromiumembedded/cef/issues/1257 for details.
            if (!command_line->HasSwitch(switches::kEnableGPU))
            {
                command_line->AppendSwitch("disable-gpu");
                command_line->AppendSwitch("disable-gpu-compositing");
            }
        }

        if (command_line->HasSwitch(switches::kUseViews) && !command_line->HasSwitch("top-chrome-md"))
        {
            // Use non-material mode on all platforms by default. Among other things
            // this causes menu buttons to show hover state. See usage of
            // MaterialDesignController::IsModeMaterial() in Chromium code.
            command_line->AppendSwitchWithValue("top-chrome-md", "non-material");
        }

        if (!command_line->HasSwitch(switches::kCachePath) && !command_line->HasSwitch("disable-gpu-shader-disk-cache"))
        {
            // Don't create a "GPUCache" directory when cache-path is unspecified.
            command_line->AppendSwitch("disable-gpu-shader-disk-cache");
        }

#if defined(OS_MACOSX)
        // Disable the toolchain prompt on macOS.
        command_line->AppendSwitch("use-mock-keychain");
#endif
    }
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
