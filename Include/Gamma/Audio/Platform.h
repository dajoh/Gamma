#ifndef GAMMA_AUDIO_PLATFORM_H
#define GAMMA_AUDIO_PLATFORM_H

#if defined(GAMMA_PLATFORM_WIN32) && defined(GAMMA_AUDIO_INTERNAL)
#define GAMMA_AUDIO_EXPORT __declspec(dllexport)
#elif defined(GAMMA_PLATFORM_WIN32) && !defined(GAMMA_AUDIO_INTERNAL)
#define GAMMA_AUDIO_EXPORT __declspec(dllimport)
#else
#define GAMMA_AUDIO_EXPORT
#endif

#endif