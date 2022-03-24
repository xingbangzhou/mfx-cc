#include "stable.h"
#include "xhcore/xhlogger.h"

#include <QDebug>

xhLogger::xhLogger(const QString& name)
    : m_name(name)
{

}

xhLogger::~xhLogger()
{

}


void xhLogger::debug(const QString& s)
{
    qDebug().nospace() << qUtf8Printable(m_name) << ": " << qUtf8Printable(s);
}

void xhLogger::info(const QString& s)
{
    qInfo().nospace() << qUtf8Printable(m_name) << ": " << qUtf8Printable(s);
}

void xhLogger::trace(const QString& s)
{
    qDebug().nospace() << qUtf8Printable(m_name) << ": " << qUtf8Printable(s);
}

void xhLogger::warn(const QString& s)
{
    qWarning().nospace() << qUtf8Printable(m_name) << ": " << qUtf8Printable(s);
}

void xhLogger::error(const QString& s)
{
    qCritical().nospace() << qUtf8Printable(m_name) << ": " << qUtf8Printable(s);
}

void xhLogger::fatal(const QString& s)
{
    qCritical().nospace() << qUtf8Printable(m_name) << ": " << qUtf8Printable(s);
}
