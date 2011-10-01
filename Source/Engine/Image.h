#ifndef IMAGE_H
#define IMAGE_H

#include <Gamma/Renderer/ITexture.h>
#include <Gamma/Engine/IImage.h>

namespace Gamma
{
	namespace Engine
	{
		class Image : public IImage
		{
		public:
			Image();
			~Image();

			bool load(const char *fileName, bool generateMipmaps);
			void unload();
			bool isLoaded() const;

			void bind(int textureUnit);
			void unbind(int textureUnit);
		private:
			bool m_loaded;
			Renderer::ITexture *m_texture;
		};
	}
}

#endif