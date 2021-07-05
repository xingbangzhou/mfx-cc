#include "stable.h"
#include "lecore/lelogger.h"

#include <QDebug>

LeLogger::LeLogger(const QString& name)
    : m_name(name)
{

}

LeLogger::~LeLogger()
{

}


void LeLogger::debug(const QString& s)
{
    qDebug().nospace() << qUtf8Printable(m_name) << ": " << qUtf8Printable(s);
}

void LeLogger::info(const QString& s)
{
    qDebug().nospace() << qUtf8Printable(m_name) << ": " << qUtf8Printable(s);
}

void LeLogger::trace(const QString& s)
{
    qDebug().nospace() << qUtf8Printable(m_name) << ": " << qUtf8Printable(s);
}

void LeLogger::warn(const QString& s)
{
    qWarning().nospace() << qUtf8Printable(m_name) << ": " << qUtf8Printable(s);
}

void LeLogger::error(const QString& s)
{
    qCritical().nospace() << qUtf8Printable(m_name) << ": " << qUtf8Printable(s);
}

void LeLogger::fatal(const QString& s)
{
    qCritical().nospace() << qUtf8Printable(m_name) << ": " << qUtf8Printable(s);
}
