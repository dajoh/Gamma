#ifndef GAMMA_ENGINE_IMODEL_H
#define GAMMA_ENGINE_IMODEL_H

namespace Gamma
{
	namespace Engine
	{
		class IModel
		{
		public:
			virtual bool load(const char *fileName) = 0;
			virtual void unload() = 0;
			virtual bool isLoaded() const = 0;

			virtual void draw() = 0;
			virtual void drawInstanced(unsigned int instances) = 0;
		};
	}
}

#endif