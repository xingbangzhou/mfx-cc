#pragma once
#include "cefcore/cefcore_global.h"
#include <QObject>

#define cefFramework CefFramework::instance()

class CEFCORE_DECL_EXPORT CefFramework : public QObject
{
    Q_OBJECT;

public:
    CefFramework();
    virtual ~CefFramework();

    static CefFramework* instance()
    {
        return self;
    }
    /*
    * @brief 初始化之前调用
    */
    void appendCmd(const QString& name, const QString& value);

    bool init(int argc, const char* const* argv);
    void uninit();

private:
    static CefFramework* self;

    QList<QPair<QString,QString>> m_cmdExtras;
    CefRefPtr<CefCommandLine> m_cmdLine;
};
