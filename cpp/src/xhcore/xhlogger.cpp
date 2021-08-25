#include "stable.h"
#include "xhcore/xhlogger.h"

#include <QDebug>

XhLogger::XhLogger(const QString& name)
    : m_name(name)
{

}

XhLogger::~XhLogger()
{

}


void XhLogger::debug(const QString& s)
{
    qDebug().nospace() << qUtf8Printable(m_name) << ": " << qUtf8Printable(s);
}

void XhLogger::info(const QString& s)
{
    qDebug().nospace() << qUtf8Printable(m_name) << ": " << qUtf8Printable(s);
}

void XhLogger::trace(const QString& s)
{
    qDebug().nospace() << qUtf8Printable(m_name) << ": " << qUtf8Printable(s);
}

void XhLogger::warn(const QString& s)
{
    qWarning().nospace() << qUtf8Printable(m_name) << ": " << qUtf8Printable(s);
}

void XhLogger::error(const QString& s)
{
    qCritical().nospace() << qUtf8Printable(m_name) << ": " << qUtf8Printable(s);
}

void XhLogger::fatal(const QString& s)
{
    qCritical().nospace() << qUtf8Printable(m_name) << ": " << qUtf8Printable(s);
}
