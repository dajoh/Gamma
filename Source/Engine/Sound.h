#ifndef SOUND_H
#define SOUND_H

#include <Gamma/Engine/ISound.h>

namespace Gamma
{
	namespace Engine
	{
		class Sound : public ISound
		{
		public:
			Sound();
			~Sound();

			bool load(const char *fileName);
			void unload();
			bool isLoaded() const;

			Audio::IBuffer *getBuffer();
		private:
			bool m_loaded;
			Audio::IBuffer *m_buffer;
		};
	}
}

#endif