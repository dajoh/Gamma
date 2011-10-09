#include <cstddef>
#include <Gamma/Utilities/Debug.h>
#include "Audio.h"
#include "Buffer.h"
#include "Source.h"

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

		bool Audio::initialize()
		{
			if(m_initialized)
			{
				return false;
			}

			m_device = alcOpenDevice(NULL);
			if(!m_device)
			{
				Utilities::printDebugString("[Gamma::Audio::Audio] Couldn't open an OpenAL device.\n");
				return false;
			}

			m_context = alcCreateContext(m_device, NULL);
			if(!m_context)
			{
				Utilities::printDebugString("[Gamma::Audio::Audio] Couldn't create an OpenAL context.\n");
				alcCloseDevice(m_device);
				return false;
			}

			if(!alcMakeContextCurrent(m_context))
			{
				Utilities::printDebugString("[Gamma::Audio::Audio] Couldn't activate the OpenAL context.\n");
				alcDestroyContext(m_context);
				alcCloseDevice(m_device);
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

			alcMakeContextCurrent(NULL);
			alcDestroyContext(m_context);
			alcCloseDevice(m_device);

			m_initialized = false;
		}

		bool Audio::isInitialized() const
		{
			return m_initialized;
		}

		IBuffer *Audio::createBuffer()
		{
			if(!m_initialized)
			{
				return NULL;
			}

			return new Buffer;
		}

		ISource *Audio::createSource()
		{
			if(!m_initialized)
			{
				return NULL;
			}

			return new Source;
		}

		void Audio::destroyBuffer(IBuffer *buffer)
		{
			if(!m_initialized)
			{
				return;
			}

			delete (Buffer *)buffer;
		}

		void Audio::destroySource(ISource *source)
		{
			if(!m_initialized)
			{
				return;
			}

			delete (Source *)source;
		}

		void Audio::setListenerPosition(const Math::Vector3 &position)
		{
			if(!m_initialized)
			{
				return;
			}

			alListenerfv(AL_POSITION, &position[0]);
		}

		void Audio::setListenerVelocity(const Math::Vector3 &velocity)
		{
			if(!m_initialized)
			{
				return;
			}

			alListenerfv(AL_VELOCITY, &velocity[0]);
		}

		void Audio::setListenerOrientation(const Math::Vector3 &forward, const Math::Vector3 &up)
		{
			if(!m_initialized)
			{
				return;
			}

			ALfloat orientation[6] = {forward.x, forward.y, forward.z, up.x, up.y, up.z};
			alListenerfv(AL_ORIENTATION, orientation);
		}

		bool Audio::update()
		{
			if(!m_initialized)
			{
				return false;
			}

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
