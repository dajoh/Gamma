#ifndef SOURCE_H
#define SOURCE_H

#include <AL/al.h>
#include <Gamma/Audio/ISource.h>

namespace Gamma
{
	namespace Audio
	{
		class Source : public ISource
		{
		public:
			Source();
			~Source();
		private:
			ALuint m_source;
		};
	}
}

#endif
