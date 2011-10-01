#ifndef RENDERER_H
#define RENDERER_H

#include <Gamma/Renderer/IRenderer.h>

namespace Gamma
{
	namespace Renderer
	{
		class Renderer : public IRenderer
		{
		public:
			Renderer();
			~Renderer();

			bool initialize();
			void uninitialize();
			bool isInitialized() const;

			IMesh *createMesh();
			IShader *createShader();
			ITexture *createTexture();
			IFramebuffer *createFramebuffer();

			void destroyMesh(IMesh *mesh);
			void destroyShader(IShader *shader);
			void destroyTexture(ITexture *texture);
			void destroyFramebuffer(IFramebuffer *framebuffer);

			bool update();

			void enableDepthTesting();
			void disableDepthTesting();

			void enableBlending();
			void disableBlending();

			void clear(float r, float g, float b, float a);
		private:
			bool m_initialized;
			int m_lastWidth, m_lastHeight;
		};

		Renderer *getInternalRenderer();
	}
}

#endif