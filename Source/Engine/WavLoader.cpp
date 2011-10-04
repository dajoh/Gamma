#include <cstdio>
#include <cstdlib>
#include "WavLoader.h"

#define ID_RIFF 0x46464952
#define ID_WAVE 0x45564157
#define ID_FORM 0x20746d66
#define ID_DATA 0x61746164

namespace Gamma
{
	namespace Engine
	{
		typedef struct
		{
			unsigned int id;
			unsigned int size;
		} ChunkHeader_t;

		typedef struct
		{
			unsigned int format;
		} RiffHeader_t;

		typedef struct
		{
			unsigned short format;
			unsigned short channels;
			unsigned int sampleRate;
			unsigned int byteRate;
			unsigned short blockAlign;
			unsigned short bitsPerSample;
		} WaveHeader_t;

		WavLoader::WavLoader() : m_loaded(false)
		{

		}

		WavLoader::~WavLoader()
		{
			if(m_loaded)
			{
				unload();
			}
		}

		bool WavLoader::load(const char *fileName)
		{
			if(m_loaded)
			{
				return false;
			}

			FILE *file = fopen(fileName, "rb");
			if(!file)
			{
				return false;
			}

			ChunkHeader_t chunkHeader;
			RiffHeader_t riffHeader;
			WaveHeader_t waveHeader;

			if(fread(&chunkHeader, 1, sizeof(ChunkHeader_t), file) != sizeof(ChunkHeader_t))
			{
				fclose(file);
				return false;
			}

			if(chunkHeader.id != ID_RIFF)
			{
				fclose(file);
				return false;
			}

			if(fread(&riffHeader, 1, sizeof(RiffHeader_t), file) != sizeof(RiffHeader_t))
			{
				fclose(file);
				return false;
			}

			if(riffHeader.format != ID_WAVE)
			{
				fclose(file);
				return false;
			}

			if(fread(&chunkHeader, 1, sizeof(ChunkHeader_t), file) != sizeof(ChunkHeader_t))
			{
				fclose(file);
				return false;
			}

			if(fread(&waveHeader, 1, sizeof(WaveHeader_t), file) != sizeof(WaveHeader_t))
			{
				fclose(file);
				return false;
			}

			if(waveHeader.format != 1)
			{
				fclose(file);
				return false;
			}

			m_channelCount = waveHeader.channels;
			m_sampleRate = waveHeader.sampleRate;
			m_sampleSize = waveHeader.bitsPerSample;

			while(1)
			{
				if(fread(&chunkHeader, 1, sizeof(ChunkHeader_t), file) != sizeof(ChunkHeader_t))
				{
					fclose(file);
					return false;
				}

				if(chunkHeader.id == ID_DATA)
				{
					m_dataSize = chunkHeader.size;
					m_data = (unsigned char *)malloc(chunkHeader.size);
					if(fread(m_data, 1, chunkHeader.size, file) != chunkHeader.size)
					{
						free(m_data);
						fclose(file);
						return false;
					}

					break;
				}

				fseek(file, chunkHeader.size, SEEK_CUR);
			}

			fclose(file);

			m_loaded = true;
			return true;
		}

		void WavLoader::unload()
		{
			if(!m_loaded)
			{
				return;
			}

			free(m_data);

			m_loaded = false;
		}

		bool WavLoader::isLoaded() const
		{
			return m_loaded;
		}

		unsigned int WavLoader::getChannelCount() const
		{
			if(!m_loaded)
			{
				return 0;
			}

			return m_channelCount;
		}

		unsigned int WavLoader::getSampleRate() const
		{
			if(!m_loaded)
			{
				return 0;
			}

			return m_sampleRate;
		}

		unsigned int WavLoader::getSampleSize() const
		{
			if(!m_loaded)
			{
				return 0;
			}

			return m_sampleSize;
		}

		unsigned int WavLoader::getDataSize() const
		{
			if(!m_loaded)
			{
				return 0;
			}

			return m_dataSize;
		}

		const void *WavLoader::getData() const
		{
			if(!m_loaded)
			{
				return NULL;
			}

			return m_data;
		}
	}
}