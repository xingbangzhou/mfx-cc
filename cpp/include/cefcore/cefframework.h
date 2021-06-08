#ifndef CEFFRAMEWORK_H
#define CEFFRAMEWORK_H

#include "cefcore/cefcore_global.h"

#include <QObject>
#include <QScopedPointer>
#include <QColor>
#include <QVector>
#include <string>

#define cefFramework CefFramework::instance()

class CefFrameworkPrivate;
class CEFCORE_DECL_EXPORT CefFramework : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(CefFramework)
public:
    explicit CefFramework();
    ~CefFramework();

    static CefFramework* instance()
    {
        return self;
    }

    enum SwitchFlag
    {
        MultiThreadedMessageLoop = 0x00000001,
        ExternalMessagePump = 0x00000002,
        OsrRenderingEnabled = 0x00000004,
        TerminateWhenAllWindowsClosed = 0x00000008
     };

    void setSwitchFlag(SwitchFlag, bool on = true);
    bool testSwitchFlag(SwitchFlag);

    // Whether OffScreenRenderingEnabled is on will be used.
    void setOsrFrameRate(int rate);
    void enableTransparentPrinting(bool enable = true);
    // Shared texture is only supported on Windows.
#if defined(Q_OS_WIN)
    void enableSharedTexture(bool enable = true);
#endif

    void enableExternalBeginFrame(bool enable = true);

    void setCachePath(const std::string& path);
    const std::string& cachePath();

    void setBackgroundColor(const QColor& color);
    const QColor& backgroundColor();

    bool initialize(int argc, const char* const* argv);

    int run();

private:
    Q_DISABLE_COPY(CefFramework)
    QScopedPointer<CefFrameworkPrivate> d_ptr;

private:
    static CefFramework* self;
};

#endif // CEFFRAMEWORK_H
