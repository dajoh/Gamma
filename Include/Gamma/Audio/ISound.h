#ifndef GAMMA_AUDIO_ISOUND_H
#define GAMMA_AUDIO_ISOUND_H

namespace Gamma
{
	namespace Audio
	{
		class ISound
		{
		public:
			virtual bool load(const char *fileName) = 0;
			virtual void unload() = 0;
			virtual bool isLoaded() const = 0;

			virtual void play() = 0;
			virtual bool isPlaying() const = 0;

			virtual bool getWaveData(float *data, unsigned int count) = 0;
		};
	}
}

#endif