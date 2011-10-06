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
		typedef enum
		{
			RendererFeature_Blending,
			RendererFeature_DepthTesting,
			RendererFeature_StencilTesting
		} RendererFeature_t;

		typedef enum
		{
			RendererBlendFunction_Zero,
			RendererBlendFunction_One,
			RendererBlendFunction_SourceColor,
			RendererBlendFunction_OneMinusSourceColor,
			RendererBlendFunction_DestinationColor,
			RendererBlendFunction_OneMinusDestinationColor,
			RendererBlendFunction_SourceAlpha,
			RendererBlendFunction_OneMinusSourceAlpha,
			RendererBlendFunction_DestinationAlpha,
			RendererBlendFunction_OneMinusDestinationAlpha,
			RendererBlendFunction_SourceAlphaSaturate
		} RendererBlendFunction_t;

		typedef enum
		{
			RendererBoolFunction_Never,
			RendererBoolFunction_Always,
			RendererBoolFunction_Equal,
			RendererBoolFunction_NotEqual,
			RendererBoolFunction_Less,
			RendererBoolFunction_LessOrEqual,
			RendererBoolFunction_Greater,
			RendererBoolFunction_GreaterOrEqual
		} RendererBoolFunction_t;

		typedef enum
		{
			RendererStencilOperation_Keep,
			RendererStencilOperation_Zero,
			RendererStencilOperation_Replace,
			RendererStencilOperation_Increment,
			RendererStencilOperation_IncrementWrap,
			RendererStencilOperation_Decrement,
			RendererStencilOperation_DecrementWrap,
			RendererStencilOperation_Invert
		} RendererStencilOperation_t;

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

			virtual void enableFeature(RendererFeature_t feature) = 0;
			virtual void disableFeature(RendererFeature_t feature) = 0;

			virtual void setBlendFunction(RendererBlendFunction_t sourceFunction, RendererBlendFunction_t destinationFunction) = 0;
			virtual void setDepthFunction(RendererBoolFunction_t depthFunction) = 0;
			virtual void setStencilFunction(RendererBoolFunction_t stencilFunction, int reference, unsigned int mask) = 0;
			virtual void setStencilOperation(RendererStencilOperation_t stencilFail, RendererStencilOperation_t depthFail, RendererStencilOperation_t pass) = 0;

			virtual void clear(float r, float g, float b, float a) = 0;
		};

		GAMMA_RENDERER_EXPORT IRenderer *getRenderer();
	}
}

#endif