#ifndef GAMMA_ENGINE_IIMAGE_H
#define GAMMA_ENGINE_IIMAGE_H

namespace Gamma
{
	namespace Engine
	{
		class IImage
		{
		public:
			virtual bool load(const char *fileName, bool generateMipmaps) = 0;
			virtual void unload() = 0;
			virtual bool isLoaded() const = 0;

			virtual void bind(int textureUnit) = 0;
			virtual void unbind(int textureUnit) = 0;
		};
	}
}

#endif