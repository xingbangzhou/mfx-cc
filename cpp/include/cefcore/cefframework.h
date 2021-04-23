#ifndef CEFFRAMEWORK_H
#define CEFFRAMEWORK_H

#include "cefcore/cefcore_global.h"

#include <QObject>
#include <QScopedPointer>

#define cefFramework CefFramework::instance()

class CefFrameworkPrivate;
class CEFCORE_DECL_EXPORT CefFramework : public QObject
{
    Q_OBJECT

    Q_DECLARE_PRIVATE(CefFramework)
public:
    CefFramework();
    virtual ~CefFramework();

    static CefFramework* instance()
    {
        return self;
    }

    void setBackgroundColor(unsigned int value);
    unsigned int backgroundColor() const;

    // 设置开关
    void appendSwtich(const QString& name, const QString& value);

    typedef std::function<int(void)> MessageLoop;
    void setMsgLoop(MessageLoop loop);

    bool init(int argc, const char* const* argv);

    int exec();

private:
    Q_DISABLE_COPY(CefFramework)
    QScopedPointer<CefFrameworkPrivate> d_ptr;

private:
    static CefFramework* self;

    unsigned int m_backgroundColor;
    MessageLoop m_msgLoop;
};

#endif // CEFFRAMEWORK_H
