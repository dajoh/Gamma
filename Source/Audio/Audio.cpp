#include <cstddef>
#include "Audio.h"
#include "Sound.h"

namespace Gamma
{
	namespace Audio
	{
		Audio::Audio() : m_initialized(false)
		{
			
		}

		Audio::~Audio()
		{
			if(m_initialized)
			{
				uninitialize();
			}
		}

		bool Audio::initialize(int maxChannels)
		{
			if(m_initialized)
			{
				return false;
			}

			if(FMOD::System_Create(&m_system) != FMOD_OK)
			{
				return false;
			}

			if(m_system->init(maxChannels, FMOD_INIT_NORMAL, NULL) != FMOD_OK)
			{
				m_system->release();
				return false;
			}

			m_initialized = true;
			return true;
		}

		void Audio::uninitialize()
		{
			if(!m_initialized)
			{
				return;
			}

			m_system->close();
			m_system->release();

			m_initialized = false;
		}

		bool Audio::isInitialized() const
		{
			return m_initialized;
		}

		ISound *Audio::createSound()
		{
			if(!m_initialized)
			{
				return NULL;
			}

			return new Sound(m_system);
		}

		void Audio::destroySound(ISound *sound)
		{
			if(!m_initialized)
			{
				return;
			}

			delete (Sound *)sound;
		}

		bool Audio::update()
		{
			if(!m_initialized)
			{
				return false;
			}

			m_system->update();
			return true;
		}

		Audio *getInternalAudio()
		{
			static Audio audio;
			return &audio;
		}

		IAudio *getAudio()
		{
			return getInternalAudio();
		}
	}
}