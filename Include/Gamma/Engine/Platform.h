#ifndef GAMMA_ENGINE_PLATFORM_H
#define GAMMA_ENGINE_PLATFORM_H

#if defined(GAMMA_PLATFORM_WIN32) && defined(GAMMA_ENGINE_INTERNAL)
#define GAMMA_ENGINE_EXPORT __declspec(dllexport)
#elif defined(GAMMA_PLATFORM_WIN32) && !defined(GAMMA_ENGINE_INTERNAL)
#define GAMMA_ENGINE_EXPORT __declspec(dllimport)
#else
#define GAMMA_ENGINE_EXPORT
#endif

#endif