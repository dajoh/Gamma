#ifndef GAMMA_AUDIO_ISOURCE_H
#define GAMMA_AUDIO_ISOURCE_H

#include "IBuffer.h"

namespace Gamma
{
	namespace Audio
	{
		class ISource
		{
		public:
			virtual void setBuffer(IBuffer *buffer) = 0;
			virtual IBuffer *getBuffer() = 0;

			virtual void play() = 0;
			virtual void pause() = 0;
			virtual void stop() = 0;
			virtual void rewind() = 0;
			virtual bool isPlaying() const = 0;

			virtual void setLooping(bool looping) = 0;
			virtual bool isLooping() const = 0;
		};
	}
}

#endif
