#include <Gamma/Utilities/Debug.h>
#include <Gamma/Renderer/IRenderer.h>
#include "TgaLoader.h"
#include "Image.h"

namespace Gamma
{
	namespace Engine
	{
		Image::Image() : m_loaded(false)
		{

		}

		Image::~Image()
		{
			if(m_loaded)
			{
				unload();
			}
		}

		bool Image::load(const char *fileName, bool generateMipmaps)
		{
			if(m_loaded)
			{
				return false;
			}

			TgaLoader tgaLoader;
			if(!tgaLoader.load(fileName))
			{
				Utilities::printDebugString("[Gamma::Engine::Image] Couldn't load %s.\n", fileName);
				return false;
			}

			Renderer::TextureFormat_t format;
			switch(tgaLoader.getFormat())
			{
			case TgaFormat_R8G8B8:
				format = Renderer::TextureFormat_RGB8;
				break;
			case TgaFormat_R8G8B8A8:
				format = Renderer::TextureFormat_RGBA8;
				break;
			default:
				Utilities::printDebugString("[Gamma::Engine::Image] %s uses an unsupported format.\n", fileName);
				return false;
			}

			m_texture = Renderer::getRenderer()->createTexture();
			m_texture->fill(format, tgaLoader.getWidth(), tgaLoader.getHeight(), tgaLoader.getData(), generateMipmaps);

			m_loaded = true;
			return true;
		}

		void Image::unload()
		{
			if(!m_loaded)
			{
				return;
			}

			Renderer::getRenderer()->destroyTexture(m_texture);

			m_loaded = false;
		}

		bool Image::isLoaded() const
		{
			return m_loaded;
		}

		void Image::bind(int textureUnit)
		{
			if(!m_loaded)
			{
				return;
			}

			m_texture->bind(textureUnit);
		}

		void Image::unbind(int textureUnit)
		{
			if(!m_loaded)
			{
				return;
			}

			m_texture->unbind(textureUnit);
		}
	}
}