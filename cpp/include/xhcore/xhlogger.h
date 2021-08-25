#ifndef XHLOGGER_H
#define XHLOGGER_H

#include <QString>

#include "xhcoreexport.h"

class XHCORE_EXPORT XhLogger
{
public:
    explicit XhLogger(const QString& name);
    virtual ~XhLogger();

    void debug(const QString& s);
    void info(const QString& s);
    void trace(const QString& s);
    void warn(const QString& s);
    void error(const QString& s);
    void fatal(const QString& s);

private:
    Q_DISABLE_COPY(XhLogger)

    QString m_name;
};

#endif // XHLOGGER_H
