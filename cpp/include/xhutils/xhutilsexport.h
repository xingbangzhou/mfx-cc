#ifndef XHUTILSEXPORT_H
#define XHUTILSEXPORT_H

#ifdef XHUTILS_IMPL
#define XHUTILS_EXPORT __declspec(dllexport)
#else
#define XHUTILS_EXPORT __declspec(dllimport)
#endif // XHUTILS_IMPL

#endif // XHUTILSEXPORT_H
