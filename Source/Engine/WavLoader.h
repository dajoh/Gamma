#ifndef WAVLOADER_H
#define WAVLOADER_H

namespace Gamma
{
	namespace Engine
	{
		class WavLoader
		{
		public:
			WavLoader();
			~WavLoader();

			bool load(const char *fileName);
			void unload();
			bool isLoaded() const;

			unsigned int getChannelCount() const;
			unsigned int getSampleRate() const;
			unsigned int getSampleSize() const;
			unsigned int getDataSize() const;

			const void *getData() const;
		private:
			bool m_loaded;
			unsigned int m_channelCount;
			unsigned int m_sampleRate;
			unsigned int m_sampleSize;
			unsigned int m_dataSize;
			unsigned char *m_data;
		};
	}
}

#endif