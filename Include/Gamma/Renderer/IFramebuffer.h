#ifndef GAMMA_RENDERER_IFRAMEBUFFER_H
#define GAMMA_RENDERER_IFRAMEBUFFER_H

#include "ITexture.h"

namespace Gamma
{
	namespace Renderer
	{
		typedef enum
		{
			FramebufferAttachPoint_Depth,
			FramebufferAttachPoint_Color0,
			FramebufferAttachPoint_Color1,
			FramebufferAttachPoint_Color2,
			FramebufferAttachPoint_Color3
		} FramebufferAttachPoint_t;

		class IFramebuffer
		{
		public:
			virtual void attachTexture(FramebufferAttachPoint_t attachPoint, ITexture *texture) = 0;

			virtual void bind() = 0;
			virtual void unbind() = 0;
		};
	}
}

#endif