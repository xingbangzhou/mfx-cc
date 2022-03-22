#ifndef BIZRELFECT_H
#define BIZRELFECT_H

#include <QObject>

class XhReflectBase
{
public:
    virtual ~XhReflectBase() = default;

    virtual const char* iid() const = 0;

    template<typename Type> 
    Type* createObject()
    {
        return reinterpret_cast<Type*>(getHolder()->createObject());
    }

protected:
    XhReflectBase() = default;

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
class XhReflectReal : public XhReflectBase
{
public:
    XhReflectReal(const char* iid)
        : m_iid(iid)
    {
    }

    const char* iid() const
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
    const char* m_iid;
};

void registerXhReflect(XhReflectBase* reflect);
void unregisterXhReflect(XhReflectBase* reflect);

#define DECLARE_BIZREFLECT(ClassName, IId) \
    private: \
    struct XhReflectHolder##ClassName \
    { \
        XhReflectReal<ClassName> reflect##ClassName; \
        XhReflectHolder##ClassName() \
            : reflect##ClassName(IId) \
        { \
            registerXhReflect(&reflect##ClassName); \
        } \
        ~XhReflectHolder##ClassName() \
        { \
            unregisterXhReflect(&reflect##ClassName); \                                                                                                         \
        } \
    } \
    static XhReflectHolder##ClassName s_xhreflectHolder##ClassName;

#define IMPLEMENT_BIZREFLECT(ClassName) \
    static ClassName::XhReflectHolder##ClassName s_xhreflectHolder##ClassName;

#endif // BIZRELFECT_H
