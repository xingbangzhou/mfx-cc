#ifndef CEFAPPRENDER_H
#define CEFAPPRENDER_H
#include "cefappbase.h"

class CefAppRender : public CefAppBase
{
public:
    CefAppRender();

private:
    IMPLEMENT_REFCOUNTING(CefAppRender);
    DISALLOW_COPY_AND_ASSIGN(CefAppRender);
};

#endif //CEFAPPRENDER_H
