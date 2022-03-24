#ifndef XHRELFECT_H
#define XHRELFECT_H

#include "xhcoreexport.h"
#include <QObject>

class xhReflect
{
public:
    virtual ~xhReflect() = default;

    virtual const QString& iid() const = 0;

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
    xhReflectHolder(const char* iid)
        : m_iid(iid)
    {
    }

    const QString& iid() const
    {
        return m_iid;
    }

protected:
    placeholder* getHolder() override
    {
        static holder<Type> _holder;
        return &_holder;
    }

private:
    QString m_iid;
};

XHCORE_EXPORT void registerXHReflect(xhReflect* reflect);
XHCORE_EXPORT void unregisterXHReflect(xhReflect* reflect);

XHCORE_EXPORT QObject* createXHObject(const QString& iid);

#define DECLARE_XHREFLECT(IFace, IId) \
    private: \
    struct xhReflectLife##IFace \
    { \
        xhReflectHolder<IFace> reflect##IFace; \
        xhReflectLife##IFace() \
            : reflect##IFace(IId) \
        {\
            registerXHReflect(&reflect##IFace); \
        }\
        ~xhReflectLife##IFace() \
        {\
            unregisterXHReflect(&reflect##IFace); \
        }\
    }; \
    static xhReflectLife##IFace s_xhreflectLife##IFace;

#define IMPLEMENT_XHREFLECT(IFace) \
    IFace::xhReflectLife##IFace IFace::s_xhreflectLife##IFace;

#endif // XHRELFECT_H
