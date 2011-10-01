#ifdef GAMMA_PLATFORM_WIN32
#include <Windows.h>
#endif

#include <cstdio>
#include <cstdarg>
#include <Gamma/Utilities/Debug.h>

namespace Gamma
{
	namespace Utilities
	{
		void printDebugString(const char *format, ...)
		{
			static char buffer[4096];

			va_list argList;
			va_start(argList, format);
			vsprintf(buffer, format, argList);
			va_end(argList);

#if defined(GAMMA_PLATFORM_LINUX) || defined(GAMMA_DEBUG)
			printf("%s", buffer);
#endif

#if defined(GAMMA_PLATFORM_WIN32)
			OutputDebugString(buffer);
#endif
		}
	}
}