#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <Gamma/Renderer/ITexture.h>

namespace Gamma
{
	namespace Renderer
	{
		class Texture : public ITexture
		{
		public:
			Texture();
			~Texture();

			void fill(TextureFormat_t format, int width, int height, const void *data, bool generateMipmaps);
			bool isFilled() const;

			void bind(int textureUnit);
			void unbind(int textureUnit);
		private:
			GLuint m_texture;
			bool m_filled;

			friend class Framebuffer;
		};
	}
}

#endif