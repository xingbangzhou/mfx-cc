#ifndef CEFFRAMEWORK_P_H
#define CEFFRAMEWORK_P_H

#include "cefcore/cefframework.h"
#include "include/internal/cef_ptr.h"
#include "include/cef_command_line.h"
#include "include/cef_app.h"
#include "messageloop.h"
#include "messageloopex.h"

#include <QList>
#include <QPair>

class CefFrameworkPrivate
{
    Q_DECLARE_PUBLIC(CefFramework)

public:
    CefFrameworkPrivate();
    ~CefFrameworkPrivate();
    CefFramework* q_ptr;

    CefRefPtr<CefApp> app;
    CefRefPtr<CefCommandLine> commandLine;
    scoped_ptr<MessageLoop> messageLoop;
    MessageLoopEx messageLoopEx;
    
    uint switchFlags;
    int osrFrameRate;
    bool transparentPrintingEnabled;
    bool externalBeginFrameEnabled;
#if defined(Q_OS_WIN)
    bool sharedTextureEnabled;
#endif

    std::string cachePath;
    QColor backgroundColor;

    bool initialize(int argc, const char* const* argv);
    void shutdown();

private:
    bool m_initialized;
    bool m_shutdown;

    void _populateSettings(CefSettings* const settings);
    void _createApp();
    void _createMessageLoop(const CefSettings* const settings);
};

#endif //CEFFRAMEWORK_P_H
