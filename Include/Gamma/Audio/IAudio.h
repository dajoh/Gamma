#ifndef GAMMA_AUDIO_IAUDIO_H
#define GAMMA_AUDIO_IAUDIO_H

#include <glm/glm.hpp>
#include "Platform.h"
#include "IBuffer.h"
#include "ISource.h"

namespace Gamma
{
	namespace Audio
	{
		class IAudio
		{
		public:
			virtual bool initialize() = 0;
			virtual void uninitialize() = 0;
			virtual bool isInitialized() const = 0;

			virtual IBuffer *createBuffer() = 0;
			virtual ISource *createSource() = 0;

			virtual void destroyBuffer(IBuffer *buffer) = 0;
			virtual void destroySource(ISource *source) = 0;

			virtual void setListenerPosition(const glm::vec3 &position) = 0;
			virtual void setListenerVelocity(const glm::vec3 &velocity) = 0;
			virtual void setListenerOrientation(const glm::vec3 &forward, const glm::vec3 &up) = 0;

			virtual bool update() = 0;
		};

		GAMMA_AUDIO_EXPORT IAudio *getAudio();
	}
}

#endif
