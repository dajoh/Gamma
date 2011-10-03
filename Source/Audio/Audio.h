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

			ISource *createSource();
			void destroySource(ISource *source);

			void setListenerPosition(const glm::vec3 &position);
			void setListenerVelocity(const glm::vec3 &velocity);
			void setListenerOrientation(const glm::vec3 &forward, const glm::vec3 &up);

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
