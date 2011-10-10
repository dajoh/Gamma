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

			void enableFeature(Feature_t feature);
			void disableFeature(Feature_t feature);

			void setCullFace(CullFace_t cullFace);
			void setBlendFunction(BlendFunction_t sourceFunction, BlendFunction_t destinationFunction);
			void setDepthFunction(CompareFunction_t depthFunction);
			void setStencilFunction(CompareFunction_t stencilFunction, int reference, unsigned int mask);
			void setStencilOperation(StencilOperation_t stencilFail, StencilOperation_t depthFail, StencilOperation_t depthPass);
			void setColorMask(bool r, bool g, bool b, bool a);
			void setDepthMask(bool depth);

			void clear(int buffers, float r, float g, float b, float a);
		private:
			bool m_initialized;
			int m_lastWidth, m_lastHeight;
		};

		Renderer *getInternalRenderer();
	}
}

#endif