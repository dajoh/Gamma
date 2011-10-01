#include "Texture.h"

namespace Gamma
{
	namespace Renderer
	{
		Texture::Texture() : m_filled(false)
		{
			glGenTextures(1, &m_texture);
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &m_texture);
		}

		void Texture::fill(TextureFormat_t format, int width, int height, const void *data, bool generateMipmaps)
		{
			GLint internalFormat;
			GLint realFormat;
			GLint type;

			switch(format)
			{
			case TextureFormat_D24:
				internalFormat = GL_DEPTH_COMPONENT24;
				realFormat = GL_DEPTH_COMPONENT;
				type = GL_UNSIGNED_BYTE;
				break;
			case TextureFormat_RGB8:
				internalFormat = GL_RGB8;
				realFormat = GL_RGB;
				type = GL_UNSIGNED_BYTE;
				break;
			case TextureFormat_RGBA8:
				internalFormat = GL_RGBA8;
				realFormat = GL_RGBA;
				type = GL_UNSIGNED_BYTE;
				break;
			case TextureFormat_RG16F:
				internalFormat = GL_RG16F;
				realFormat = GL_RG;
				type = GL_FLOAT;
				break;
			default:
				return;
			}

			glBindTexture(GL_TEXTURE_2D, m_texture);
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, realFormat, type, data);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			if(generateMipmaps)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			}

			glBindTexture(GL_TEXTURE_2D, 0);

			m_filled = true;
		}

		bool Texture::isFilled() const
		{
			return m_filled;
		}

		void Texture::bind(int textureUnit)
		{
			if(!m_filled)
			{
				return;
			}

			glActiveTexture(GL_TEXTURE0 + textureUnit);
			glBindTexture(GL_TEXTURE_2D, m_texture);
		}

		void Texture::unbind(int textureUnit)
		{
			if(!m_filled)
			{
				return;
			}

			glActiveTexture(GL_TEXTURE0 + textureUnit);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}