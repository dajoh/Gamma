#include "Buffer.h"

namespace Gamma
{
	namespace Audio
	{
		Buffer::Buffer() : m_filled(false)
		{
			alGenBuffers(1, &m_buffer);
		}

		Buffer::~Buffer()
		{
			alDeleteBuffers(1, &m_buffer);
		}

		bool Buffer::fill(BufferFormat_t format, const void *data, unsigned int size, unsigned int frequency)
		{
			ALenum realFormat;
			switch(format)
			{
			case BufferFormat_Mono8:
				realFormat = AL_FORMAT_MONO8;
				break;
			case BufferFormat_Mono16:
				realFormat = AL_FORMAT_MONO16;
				break;
			case BufferFormat_Stereo8:
				realFormat = AL_FORMAT_STEREO8;
				break;
			case BufferFormat_Stereo16:
				realFormat = AL_FORMAT_STEREO16;
				break;
			default:
				return false;
			}

			// Clear the error state, then fill the buffer.
			alGetError();
			alBufferData(m_buffer, realFormat, data, size, frequency);

			// Check if an error occured.
			if(alGetError() != AL_NO_ERROR)
			{
				return false;
			}

			m_filled = true;
			return true;
		}

		bool Buffer::isFilled() const
		{
			return m_filled;
		}
	}
}
