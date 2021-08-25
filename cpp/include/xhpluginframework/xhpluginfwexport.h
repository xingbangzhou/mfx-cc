#ifndef XHPLUGINFWEXPORT_H
#define XHPLUGINFWEXPORT_H

#ifdef XHPLUGINFW_IMPL
#define XHPLUGINFW_EXPORT __declspec(dllexport)
#else
#define XHPLUGINFW_EXPORT __declspec(dllimport)
#endif // XHPLUGINFW_IMPL

#endif // XHPLUGINFWEXPORT_H
