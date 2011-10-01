#ifndef GAMMA_AUDIO_IAUDIO_H
#define GAMMA_AUDIO_IAUDIO_H

#include "Platform.h"
#include "ISound.h"

namespace Gamma
{
	namespace Audio
	{
		class IAudio
		{
		public:
			virtual bool initialize(int maxChannels) = 0;
			virtual void uninitialize() = 0;
			virtual bool isInitialized() const = 0;

			virtual ISound *createSound() = 0;
			virtual void destroySound(ISound *sound) = 0;

			virtual bool update() = 0;
		};
		
		GAMMA_AUDIO_EXPORT IAudio *getAudio();
	}
}

#endif