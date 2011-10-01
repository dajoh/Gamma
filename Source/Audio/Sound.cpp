#include <cstddef>
#include "Sound.h"
#include "Audio.h"

namespace Gamma
{
	namespace Audio
	{
		Sound::Sound(FMOD::System *system) : m_loaded(false), m_system(system), m_channel(NULL)
		{

		}

		Sound::~Sound()
		{
			if(m_loaded)
			{
				unload();
			}
		}

		bool Sound::load(const char *fileName)
		{
			if(m_loaded)
			{
				return false;
			}

			m_system->createStream(fileName, FMOD_DEFAULT, NULL, &m_sound);
			if(!m_sound)
			{
				return false;
			}

			m_loaded = true;
			return true;
		}

		void Sound::unload()
		{
			if(!m_loaded)
			{
				return;
			}

			m_sound->release();

			m_loaded = false;
		}

		bool Sound::isLoaded() const
		{
			return m_loaded;
		}

		void Sound::play()
		{
			if(!m_loaded)
			{
				return;
			}

			m_system->playSound(FMOD_CHANNEL_FREE, m_sound, false, &m_channel);
		}

		bool Sound::isPlaying() const
		{
			if(!m_loaded || !m_channel)
			{
				return false;
			}

			bool isPlaying;
			m_channel->isPlaying(&isPlaying);
			return isPlaying;
		}

		bool Sound::getWaveData(float *data, unsigned int count)
		{
			if(!m_loaded || !m_channel)
			{
				return false;
			}

			return m_channel->getWaveData(data, count, 0) == FMOD_OK;
		}
	}
}