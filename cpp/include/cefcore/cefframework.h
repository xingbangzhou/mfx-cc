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

    bool init();
    void uninit();

private:
    static CefFramework* self;
};
