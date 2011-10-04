#ifndef SOURCE_H
#define SOURCE_H

#include <AL/al.h>
#include <Gamma/Audio/ISource.h>
#include "Buffer.h"

namespace Gamma
{
	namespace Audio
	{
		class Source : public ISource
		{
		public:
			Source();
			~Source();

			void setBuffer(IBuffer *buffer);
			IBuffer *getBuffer();

			void play();
			void pause();
			void stop();
			void rewind();
			bool isPlaying() const;

			void setLooping(bool looping);
			bool isLooping() const;
		private:
			ALuint m_source;
			Buffer *m_buffer;
		};
	}
}

#endif
