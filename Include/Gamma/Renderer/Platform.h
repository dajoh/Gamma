#ifndef GAMMA_RENDERER_PLATFORM_H
#define GAMMA_RENDERER_PLATFORM_H

#if defined(GAMMA_PLATFORM_WIN32) && defined(GAMMA_RENDERER_INTERNAL)
#define GAMMA_RENDERER_EXPORT __declspec(dllexport)
#elif defined(GAMMA_PLATFORM_WIN32) && !defined(GAMMA_RENDERER_INTERNAL)
#define GAMMA_RENDERER_EXPORT __declspec(dllimport)
#else
#define GAMMA_RENDERER_EXPORT
#endif

#endif