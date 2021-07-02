#ifndef LEPLUGINFWEXPORT_H
#define LEPLUGINFWEXPORT_H

#ifdef LEPLUGINFW_IMPL
#define LEPLUGINFW_EXPORT __declspec(dllexport)
#else
#define LEPLUGINFW_EXPORT __declspec(dllimport)
#endif // LEPLUGINFW_IMPL

#endif // LEPLUGINFWEXPORT_H
