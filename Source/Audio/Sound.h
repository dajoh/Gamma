#ifndef SOUND_H
#define SOUND_H

#include <fmod/fmod.hpp>
#include <Gamma/Audio/ISound.h>

namespace Gamma
{
	namespace Audio
	{
		class Sound : public ISound
		{
		public:
			Sound(FMOD::System *system);
			~Sound();

			bool load(const char *fileName);
			void unload();
			bool isLoaded() const;

			void play();
			bool isPlaying() const;

			bool getWaveData(float *data, unsigned int count);
		private:
			bool m_loaded;
			FMOD::System *m_system;
			FMOD::Sound *m_sound;
			FMOD::Channel *m_channel;
		};
	}
}

#endif