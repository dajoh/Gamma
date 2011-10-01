#ifndef AUDIO_H
#define AUDIO_H

#include <fmod/fmod.hpp>
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

			bool initialize(int maxChannels);
			void uninitialize();
			bool isInitialized() const;

			ISound *createSound();
			void destroySound(ISound *sound);

			bool update();
		private:
			bool m_initialized;
			FMOD::System *m_system;
		};

		Audio *getInternalAudio();
	}
}

#endif