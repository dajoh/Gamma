#ifndef GAMMA_ENGINE_ISOUND_H
#define GAMMA_ENGINE_ISOUND_H

#include <Gamma/Audio/IBuffer.h>

namespace Gamma
{
	namespace Engine
	{
		class ISound
		{
		public:
			virtual bool load(const char *fileName) = 0;
			virtual void unload() = 0;
			virtual bool isLoaded() const = 0;

			virtual Audio::IBuffer *getBuffer() = 0;
		};
	}
}

#endif