#ifndef AUDIO_H
#define AUDIO_H

#include <AL/alc.h>
#include <Gamma/Audio/IAudio.h>

namespace Gamma
{
	namespace Audio
	{
		class Audio : public IAudio
		{
		public:
			Audio();
			~Audio();

			bool initialize();
			void uninitialize();
			bool isInitialized() const;

			IBuffer *createBuffer();
			ISource *createSource();

			void destroyBuffer(IBuffer *buffer);
			void destroySource(ISource *source);

			void setListenerPosition(const Math::Vector3 &position);
			void setListenerVelocity(const Math::Vector3 &velocity);
			void setListenerOrientation(const Math::Vector3 &forward, const Math::Vector3 &up);

			bool update();
		private:
			bool m_initialized;
			ALCdevice *m_device;
			ALCcontext *m_context;
		};

		Audio *getInternalAudio();
	}
}

#endif
