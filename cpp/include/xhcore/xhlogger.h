#ifndef XHLOGGER_H
#define XHLOGGER_H

#include "xhcoreexport.h"
#include <QString>

class XHCORE_EXPORT xhLogger
{
public:
    explicit xhLogger(const QString& name);
    virtual ~xhLogger();

    void debug(const QString& s);
    void info(const QString& s);
    void trace(const QString& s);
    void warn(const QString& s);
    void error(const QString& s);
    void fatal(const QString& s);

private:
    Q_DISABLE_COPY(xhLogger)

    QString m_name;
};

#endif // XHLOGGER_H
