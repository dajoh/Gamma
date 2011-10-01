#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GL/glew.h>
#include <Gamma/Renderer/IFramebuffer.h>

namespace Gamma
{
	namespace Renderer
	{
		class Framebuffer : public IFramebuffer
		{
		public:
			Framebuffer();
			~Framebuffer();

			void attachTexture(FramebufferAttachPoint_t attachPoint, ITexture *texture);

			void bind();
			void unbind();
		private:
			GLuint m_framebuffer;
			GLenum m_buffers[5];
			GLint m_bufferCount;
		};
	}
}

#endif