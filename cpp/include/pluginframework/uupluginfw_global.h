#ifndef UUPLUGINFW_GLOBAL_H
#define UUPLUGINFW_GLOBAL_H

#ifdef UUPLUGINFW_IMPL
#define UUPLUGINFW_EXPORT __declspec(dllexport)
#else
#define UUPLUGINFW_EXPORT __declspec(dllimport)
#endif // UUPLUGINFW_IMPL

#endif // UUPLUGINFW_GLOBAL_H
