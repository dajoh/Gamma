#include <cstddef>
#include <Gamma/Utilities/Debug.h>
#include <Gamma/Audio/IAudio.h>
#include "WavLoader.h"
#include "Sound.h"

namespace Gamma
{
	namespace Engine
	{
		Sound::Sound() : m_loaded(false)
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

			WavLoader wavLoader;
			if(!wavLoader.load(fileName))
			{
				Utilities::printDebugString("[Gamma::Engine::Sound] Couldn't load %s.\n", fileName);
				return false;
			}

			Audio::BufferFormat_t bufferFormat;
			if(wavLoader.getSampleSize() == 8 && wavLoader.getChannelCount() == 1)
			{
				bufferFormat = Audio::BufferFormat_Mono8;
			}
			else if(wavLoader.getSampleSize() == 16 && wavLoader.getChannelCount() == 1)
			{
				bufferFormat = Audio::BufferFormat_Mono16;
			}
			else if(wavLoader.getSampleSize() == 8 && wavLoader.getChannelCount() == 2)
			{
				bufferFormat = Audio::BufferFormat_Stereo8;
			}
			else if(wavLoader.getSampleSize() == 16 && wavLoader.getChannelCount() == 2)
			{
				bufferFormat = Audio::BufferFormat_Stereo16;
			}
			else
			{
				Utilities::printDebugString("[Gamma::Engine::Sound] %s uses an unsupported format.\n", fileName);
				wavLoader.unload();
				return false;
			}

			m_buffer = Audio::getAudio()->createBuffer();
			m_buffer->fill(bufferFormat, wavLoader.getData(), wavLoader.getDataSize(), wavLoader.getSampleRate());

			m_loaded = true;
			return true;
		}

		void Sound::unload()
		{
			if(!m_loaded)
			{
				return;
			}

			Audio::getAudio()->destroyBuffer(m_buffer);

			m_loaded = false;
		}

		bool Sound::isLoaded() const
		{
			return m_loaded;
		}

		Audio::IBuffer *Sound::getBuffer()
		{
			if(!m_loaded)
			{
				return NULL;
			}

			return m_buffer;
		}
	}
}