#ifndef GAMMA_RENDERER_ITEXTURE_H
#define GAMMA_RENDERER_ITEXTURE_H

namespace Gamma
{
	namespace Renderer
	{
		typedef enum
		{
			TextureFormat_D24,
			TextureFormat_RGB8,
			TextureFormat_RGBA8,
			TextureFormat_RG16F
		} TextureFormat_t;

		class ITexture
		{
		public:
			virtual void fill(TextureFormat_t format, int width, int height, const void *data, bool generateMipmaps) = 0;
			virtual bool isFilled() const = 0;

			virtual void bind(int textureUnit) = 0;
			virtual void unbind(int textureUnit) = 0;
		};
	}
}

#endif