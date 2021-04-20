#pragma once
#include "cefcore/cefcore_global.h"
#include <QObject>

#define cefFramework CefFramework::instance()

class CEFCORE_DECL_EXPORT CefFramework : public QObject
{
    Q_OBJECT;
    Q_DECLARE_PRIVATE(CefFramework)

public:
    CefFramework();
    virtual ~CefFramework();

    static CefFramework* instance()
    {
        return self;
    }

    // 调用时机：初始化前
    void appendSwtich(const QString& name, const QString& value);

    int init(int argc, const char* const* argv);
    void uninit();

protected:
    Q_DISABLE_COPY(CefFramework)

    QScopedPointer<CefFrameworkPrivate> d_ptr;

private:
    static CefFramework* self;
};
