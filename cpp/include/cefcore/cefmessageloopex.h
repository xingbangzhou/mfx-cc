#ifndef CEFMESSAGELOOPEX_H
#define CEFMESSAGELOOPEX_H

#include <functional>

class CefMessageLoopEx {
public:
    virtual ~CefMessageLoopEx() {}

    typedef std::function<int()> ExternalRunner;
    virtual void setRunner(ExternalRunner runner) = 0;

protected:
    explicit CefMessageLoopEx() {}
};

#endif // CefMessageLoopEx
