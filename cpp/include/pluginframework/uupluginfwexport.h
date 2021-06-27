#ifndef UUPLUGINFWEXPORT_H
#define UUPLUGINFWEXPORT_H

#ifdef UUPLUGINFW_IMPL
#define UUPLUGINFW_EXPORT __declspec(dllexport)
#else
#define UUPLUGINFW_EXPORT __declspec(dllimport)
#endif // UUPLUGINFW_IMPL

#endif // UUPLUGINFWEXPORT_H
