#ifndef LELOGGER_H
#define LELOGGER_H

#include <QString>

#include "lecoreexport.h"

class LECORE_EXPORT LeLogger
{
public:
    explicit LeLogger(const QString& name);
    virtual ~LeLogger();

    void debug(const QString& s);
    void info(const QString& s);
    void trace(const QString& s);
    void warn(const QString& s);
    void error(const QString& s);
    void fatal(const QString& s);

private:
    Q_DISABLE_COPY(LeLogger)

    QString m_name;
};

#endif // LELOGGER_H
