#include <cstddef>
#include "Buffer.h"
#include "Source.h"

namespace Gamma
{
	namespace Audio
	{
		Source::Source() : m_buffer(NULL)
		{
			alGenSources(1, &m_source);
		}

		Source::~Source()
		{
			alDeleteSources(1, &m_source);
		}

		void Source::setBuffer(IBuffer *buffer)
		{
			if(isPlaying())
			{
				stop();
			}

			if(buffer)
			{
				alSourcei(m_source, AL_BUFFER, ((Buffer *)buffer)->m_buffer);
			}
			else
			{
				alSourcei(m_source, AL_BUFFER, AL_NONE);
			}

			m_buffer = buffer;
		}

		IBuffer *Source::getBuffer()
		{
			return m_buffer;
		}

		void Source::play()
		{
			alSourcePlay(m_source);
		}

		void Source::pause()
		{
			alSourcePause(m_source);
		}

		void Source::stop()
		{
			alSourceStop(m_source);
		}

		void Source::rewind()
		{
			alSourceRewind(m_source);
		}

		bool Source::isPlaying() const
		{
			int state;
			alGetSourcei(m_source, AL_SOURCE_STATE, &state);
			return state == AL_PLAYING;
		}

		void Source::setLooping(bool looping)
		{
			alSourcei(m_source, AL_LOOPING, looping ? AL_TRUE : AL_FALSE);
		}

		bool Source::isLooping() const
		{
			int looping;
			alGetSourcei(m_source, AL_LOOPING, &looping);
			return looping == AL_TRUE;
		}
	}
}
