#pragma once

#include <qglobal.h>
#include <stdint.h>

#ifdef CEFCORE_IMPL
#define CEFCORE_DECL_EXPORT __declspec(dllexport)
#else
#define CEFCORE_DECL_EXPORT __declspec(dllimport)
#endif
