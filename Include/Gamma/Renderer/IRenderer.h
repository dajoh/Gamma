#ifndef GAMMA_RENDERER_IRENDERER_H
#define GAMMA_RENDERER_IRENDERER_H

#include "Platform.h"
#include "IMesh.h"
#include "IShader.h"
#include "ITexture.h"
#include "IFramebuffer.h"

namespace Gamma
{
	namespace Renderer
	{
		class IRenderer
		{
		public:
			virtual bool initialize() = 0;
			virtual void uninitialize() = 0;
			virtual bool isInitialized() const = 0;

			virtual IMesh *createMesh() = 0;
			virtual IShader *createShader() = 0;
			virtual ITexture *createTexture() = 0;
			virtual IFramebuffer *createFramebuffer() = 0;

			virtual void destroyMesh(IMesh *mesh) = 0;
			virtual void destroyShader(IShader *shader) = 0;
			virtual void destroyTexture(ITexture *texture) = 0;
			virtual void destroyFramebuffer(IFramebuffer *framebuffer) = 0;

			virtual bool update() = 0;

			virtual void enableDepthTesting() = 0;
			virtual void disableDepthTesting() = 0;

			virtual void enableBlending() = 0;
			virtual void disableBlending() = 0;

			virtual void clear(float r, float g, float b, float a) = 0;
		};

		GAMMA_RENDERER_EXPORT IRenderer *getRenderer();
	}
}

#endif