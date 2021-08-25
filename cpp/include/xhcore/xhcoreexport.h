#ifndef XHCOREEXPORT_H
#define XHCOREEXPORT_H

#ifdef XHCORE_IMPL
#define XHCORE_EXPORT __declspec(dllexport)
#else
#define XHCORE_EXPORT __declspec(dllimport)
#endif // XHCORE_IMPL

#endif // XHCOREEXPORT_H
