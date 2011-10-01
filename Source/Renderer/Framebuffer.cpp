#include "Framebuffer.h"
#include "Texture.h"

namespace Gamma
{
	namespace Renderer
	{
		Framebuffer::Framebuffer() : m_bufferCount(0)
		{
			glGenFramebuffers(1, &m_framebuffer);
		}

		Framebuffer::~Framebuffer()
		{
			glDeleteFramebuffers(1, &m_framebuffer);
		}

		void Framebuffer::attachTexture(FramebufferAttachPoint_t attachPoint, ITexture *texture)
		{
			Texture *internalTexture = dynamic_cast<Texture *>(texture);
			if(!internalTexture)
			{
				return;
			}

			GLint attachment;
			switch(attachPoint)
			{
			case FramebufferAttachPoint_Depth:
				attachment = GL_DEPTH_ATTACHMENT;
				break;
			case FramebufferAttachPoint_Color0:
				attachment = GL_COLOR_ATTACHMENT0;
				break;
			case FramebufferAttachPoint_Color1:
				attachment = GL_COLOR_ATTACHMENT1;
				break;
			case FramebufferAttachPoint_Color2:
				attachment = GL_COLOR_ATTACHMENT2;
				break;
			case FramebufferAttachPoint_Color3:
				attachment = GL_COLOR_ATTACHMENT3;
				break;
			default:
				return;
			}

			if(attachment != GL_DEPTH_ATTACHMENT)
			{
				bool found = false;
				for(int i = 0; i < m_bufferCount; i++)
				{
					if(m_buffers[i] == attachment)
					{
						found = true;
					}
				}

				if(!found)
				{
					m_buffers[m_bufferCount++] = attachment;
				}
			}

			glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
			glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, internalTexture->m_texture, 0);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void Framebuffer::bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
			glDrawBuffers(m_bufferCount, m_buffers);
		}

		void Framebuffer::unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}