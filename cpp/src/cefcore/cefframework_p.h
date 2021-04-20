#ifndef CEFFRAMEWORK_P_H
#define CEFFRAMEWORK_P_H

#include "include/internal/cef_ptr.h"
#include "include/cef_command_line.h"
#include "cefcore/cefframework.h"

class CefFrameworkPrivate : public QObjectData
{
    Q_DECLARE_PUBLIC(CefFramework)

public:
    CefFrameworkPrivate();
    virtual ~CefFrameworkPrivate();
    CefFramework* q_ptr;

    QList<QPair<QString, QString>> switchList;
    CefRefPtr<CefCommandLine> commandLine;

public:
    int initEnv(int argc, const char* const* argv);
    void uninitEnv();
};

#endif //CEFFRAMEWORK_P_H
