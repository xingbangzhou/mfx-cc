#include "stable.h"
#include "cefframework.h"

CefFramework* CefFramework::self = nullptr;

CefFramework::CefFramework()
{
    self = this;
}

CefFramework::~CefFramework()
{

}

bool CefFramework::init()
{
    return true;
}

void CefFramework::uninit()
{

}
