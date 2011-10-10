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
			Feature_Culling,
			Feature_Blending,
			Feature_DepthTesting,
			Feature_StencilTesting
		} Feature_t;

		typedef enum
		{
			CullFace_Back,
			CullFace_Front
		} CullFace_t;

		typedef enum
		{
			BlendFunction_Zero,
			BlendFunction_One,
			BlendFunction_SourceColor,
			BlendFunction_OneMinusSourceColor,
			BlendFunction_DestinationColor,
			BlendFunction_OneMinusDestinationColor,
			BlendFunction_SourceAlpha,
			BlendFunction_OneMinusSourceAlpha,
			BlendFunction_DestinationAlpha,
			BlendFunction_OneMinusDestinationAlpha,
			BlendFunction_SourceAlphaSaturate
		} BlendFunction_t;

		typedef enum
		{
			CompareFunction_Never,
			CompareFunction_Always,
			CompareFunction_Equal,
			CompareFunction_NotEqual,
			CompareFunction_Less,
			CompareFunction_LessOrEqual,
			CompareFunction_Greater,
			CompareFunction_GreaterOrEqual
		} CompareFunction_t;

		typedef enum
		{
			StencilOperation_Keep,
			StencilOperation_Zero,
			StencilOperation_Replace,
			StencilOperation_Increment,
			StencilOperation_IncrementWrap,
			StencilOperation_Decrement,
			StencilOperation_DecrementWrap,
			StencilOperation_Invert
		} StencilOperation_t;

		typedef enum
		{
			Buffer_Color = 0x01,
			Buffer_Depth = 0x02,
			Buffer_Stencil = 0x04
		} Buffer_t;

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

			virtual void enableFeature(Feature_t feature) = 0;
			virtual void disableFeature(Feature_t feature) = 0;

			virtual void setCullFace(CullFace_t cullFace) = 0;
			virtual void setBlendFunction(BlendFunction_t sourceFunction, BlendFunction_t destinationFunction) = 0;
			virtual void setDepthFunction(CompareFunction_t depthFunction) = 0;
			virtual void setStencilFunction(CompareFunction_t stencilFunction, int reference, unsigned int mask) = 0;
			virtual void setStencilOperation(StencilOperation_t stencilFail, StencilOperation_t depthFail, StencilOperation_t depthPass) = 0;
			virtual void setColorMask(bool r, bool g, bool b, bool a) = 0;
			virtual void setDepthMask(bool depth) = 0;

			virtual void clear(int buffers, float r, float g, float b, float a) = 0;
		};

		GAMMA_RENDERER_EXPORT IRenderer *getRenderer();
	}
}

#endif