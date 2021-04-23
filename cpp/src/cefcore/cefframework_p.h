#ifndef CEFFRAMEWORK_P_H
#define CEFFRAMEWORK_P_H

#include "cefcore/cefframework.h"
#include "include/internal/cef_ptr.h"
#include "include/cef_command_line.h"
#include "include/cef_app.h"

#include <QList>
#include <QPair>
#include <QString>

class CefFrameworkPrivate
{
    Q_DECLARE_PUBLIC(CefFramework)

public:
    CefFrameworkPrivate();
    ~CefFrameworkPrivate();
    CefFramework* q_ptr;

    CefRefPtr<CefApp> app;
    QList<QPair<QString, QString>> switchList;
    CefRefPtr<CefCommandLine> commandLine;
    bool initialized;

public:
    bool initEnv(int argc, const char* const* argv);
    void uninitEnv();
};

#endif //CEFFRAMEWORK_P_H
