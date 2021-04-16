#ifndef CEFCORE_GLOBAL_H
#define CEFCORE_GLOBAL_H

#include <qglobal.h>
#include <stdint.h>

#ifdef CEFCORE_IMPL
#define CEFCORE_DECL_EXPORT __declspec(dllexport)
#else
#define CEFCORE_DECL_EXPORT __declspec(dllimport)
#endif // CEFCORE_IMPL

#endif // CEFCORE_GLOBAL_H
