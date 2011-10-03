#include "Source.h"

namespace Gamma
{
	namespace Audio
	{
		Source::Source()
		{
			alGenSources(1, &m_source);
		}

		Source::~Source()
		{
			alDeleteSources(1, &m_source);
		}
	}
}
