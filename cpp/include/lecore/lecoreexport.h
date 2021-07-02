#ifndef LECOREEXPORT_H
#define LECOREEXPORT_H

#ifdef LECORE_IMPL
#define LECORE_EXPORT __declspec(dllexport)
#else
#define LECORE_EXPORT __declspec(dllimport)
#endif // LECORE_IMPL

#endif // LECOREEXPORT_H
