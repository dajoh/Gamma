#ifndef GAMMA_AUDIO_IBUFFER_H
#define GAMMA_AUDIO_IBUFFER_H

namespace Gamma
{
	namespace Audio
	{
		typedef enum
		{
			BufferFormat_Mono8,
			BufferFormat_Mono16,
			BufferFormat_Stereo8,
			BufferFormat_Stereo16
		} BufferFormat_t;

		class IBuffer
		{
		public:
			virtual bool fill(BufferFormat_t format, const void *data, unsigned int size, unsigned int frequency) = 0;
			virtual bool isFilled() const = 0;
		};
	}
}

#endif
