#ifndef XHRELFECT_H
#define XHRELFECT_H

#include "xhcoreexport.h"
#include <QObject>

class xhReflect
{
public:
    virtual ~xhReflect() = default;

    virtual const QString& cid() const = 0;

    template<typename Type> 
    Type* createObject()
    {
        return reinterpret_cast<Type*>(getHolder()->createObject());
    }
    QObject* createObject()
    {
        return getHolder()->createObject();
    }

protected:
    xhReflect() = default;

    struct placeholder
    {
    public:
        ~placeholder() = default;

        virtual QObject* createObject() = 0;
    };

    template <typename Type> class holder : public placeholder
    {
        virtual QObject* createObject() override
        {
            return new Type();
        }
    };

    virtual placeholder* getHolder() = 0;
};

template <typename Type> 
class xhReflectHolder : public xhReflect
{
public:
    xhReflectHolder(const char* cid)
        : m_cid(cid)
    {
    }

    const QString& cid() const
    {
        return m_cid;
    }

protected:
    placeholder* getHolder() override
    {
        static holder<Type> _holder;
        return &_holder;
    }

private:
    QString m_cid;
};

XHCORE_EXPORT void xh_registerReflect(xhReflect* reflect);
XHCORE_EXPORT void xh_unregisterReflect(xhReflect* reflect);

XHCORE_EXPORT QObject* xh_createObject(const QString& cid);

#define DECLARE_XHREFLECT(Class, cid) \
    private: \
    struct xhReflectLife##Class \
    { \
        xhReflectHolder<Class> reflect##Class; \
        xhReflectLife##Class() \
            : reflect##Class(cid) \
        {\
            xh_registerReflect(&reflect##Class); \
        }\
        ~xhReflectLife##Class() \
        {\
            xh_unregisterReflect(&reflect##Class); \
        }\
    }; \
    static xhReflectLife##Class s_xhreflectLife##Class;

#define IMPLEMENT_XHREFLECT(Class) \
    Class::xhReflectLife##Class Class::s_xhreflectLife##Class;

#endif // XHRELFECT_H
