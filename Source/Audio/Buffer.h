#ifndef BUFFER_H
#define BUFFER_H

#include <AL/al.h>
#include <Gamma/Audio/IBuffer.h>

namespace Gamma
{
	namespace Audio
	{
		class Buffer : public IBuffer
		{
		public:
			Buffer();
			~Buffer();

			bool fill(BufferFormat_t format, const void *data, unsigned int size, unsigned int frequency);
			bool isFilled() const;
		private:
			ALuint m_buffer;
			bool m_filled;

			friend class Source;
		};
	}
}

#endif
