#include <GL/glew.h>
#include <Gamma/Utilities/Debug.h>
#include <Gamma/Renderer/IWindow.h>
#include "Renderer.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Framebuffer.h"

namespace Gamma
{
	namespace Renderer
	{
		static inline GLenum getFeature(Feature_t feature)
		{
			switch(feature)
			{
			case Feature_Culling:
				return GL_CULL_FACE;
			case Feature_Blending:
				return GL_BLEND;
			case Feature_DepthTesting:
				return GL_DEPTH_TEST;
			case Feature_StencilTesting:
				return GL_STENCIL_TEST;
			default:
				return 0;
			}
		}

		static inline GLenum getCullFace(CullFace_t cullFace)
		{
			switch(cullFace)
			{
			case CullFace_Back:
				return GL_BACK;
			case CullFace_Front:
				return GL_FRONT;
			default:
				return 0;
			}
		}

		static inline GLenum getBlendFunction(BlendFunction_t blendFunction)
		{
			switch(blendFunction)
			{
			case BlendFunction_Zero:
				return GL_ZERO;
			case BlendFunction_One:
				return GL_ONE;
			case BlendFunction_SourceColor:
				return GL_SRC_COLOR;
			case BlendFunction_OneMinusSourceColor:
				return GL_ONE_MINUS_SRC_COLOR;
			case BlendFunction_DestinationColor:
				return GL_DST_COLOR;
			case BlendFunction_OneMinusDestinationColor:
				return GL_ONE_MINUS_DST_COLOR;
			case BlendFunction_SourceAlpha:
				return GL_SRC_ALPHA;
			case BlendFunction_OneMinusSourceAlpha:
				return GL_ONE_MINUS_SRC_ALPHA;
			case BlendFunction_DestinationAlpha:
				return GL_DST_ALPHA;
			case BlendFunction_OneMinusDestinationAlpha:
				return GL_ONE_MINUS_DST_ALPHA;
			case BlendFunction_SourceAlphaSaturate:
				return GL_SRC_ALPHA_SATURATE;
			default:
				return 0;
			}
		}

		static inline GLenum getCompareFunction(CompareFunction_t compareFunction)
		{
			switch(compareFunction)
			{
			case CompareFunction_Never:
				return GL_NEVER;
			case CompareFunction_Always:
				return GL_ALWAYS;
			case CompareFunction_Equal:
				return GL_EQUAL;
			case CompareFunction_NotEqual:
				return GL_NOTEQUAL;
			case CompareFunction_Less:
				return GL_LESS;
			case CompareFunction_LessOrEqual:
				return GL_LEQUAL;
			case CompareFunction_Greater:
				return GL_GREATER;
			case CompareFunction_GreaterOrEqual:
				return GL_GEQUAL;
			default:
				return 0;
			}
		}

		static inline GLenum getStencilOperation(StencilOperation_t stencilOperation)
		{
			switch(stencilOperation)
			{
			case StencilOperation_Keep:
				return GL_KEEP;
			case StencilOperation_Zero:
				return GL_ZERO;
			case StencilOperation_Replace:
				return GL_REPLACE;
			case StencilOperation_Increment:
				return GL_INCR;
			case StencilOperation_IncrementWrap:
				return GL_INCR_WRAP;
			case StencilOperation_Decrement:
				return GL_DECR;
			case StencilOperation_DecrementWrap:
				return GL_DECR_WRAP;
			case StencilOperation_Invert:
				return GL_INVERT;
			default:
				return 0;
			}
		}

		static inline GLenum getBuffers(int buffers)
		{
			GLenum mask = 0;

			if(buffers & Buffer_Color)
			{
				mask |= GL_COLOR_BUFFER_BIT;
			}

			if(buffers & Buffer_Depth)
			{
				mask |= GL_DEPTH_BUFFER_BIT;
			}

			if(buffers & Buffer_Stencil)
			{
				mask |= GL_STENCIL_BUFFER_BIT;
			}

			return mask;
		}

		Renderer::Renderer() : m_initialized(false)
		{

		}

		Renderer::~Renderer()
		{
			if(m_initialized)
			{
				uninitialize();
			}
		}

		bool Renderer::initialize()
		{
			if(m_initialized || !getWindow()->isCreated())
			{
				return false;
			}

			// We need to turn this on for some functions.
			glewExperimental = 1;

			// Initialize GLEW.
			if(glewInit() != GLEW_OK)
			{
				return false;
			}

			// Set up the viewport.
			getWindow()->getSize(&m_lastWidth, &m_lastHeight);
			glViewport(0, 0, m_lastWidth, m_lastHeight);

			// Front face is clockwise.
			glFrontFace(GL_CW);

			m_initialized = true;
			return true;
		}

		void Renderer::uninitialize()
		{
			if(!m_initialized)
			{
				return;
			}

			m_initialized = false;
		}

		bool Renderer::isInitialized() const
		{
			return m_initialized;
		}

		IMesh *Renderer::createMesh()
		{
			if(!m_initialized)
			{
				return NULL;
			}

			return new Mesh;
		}

		IShader *Renderer::createShader()
		{
			if(!m_initialized)
			{
				return NULL;
			}

			return new Shader;
		}

		ITexture *Renderer::createTexture()
		{
			if(!m_initialized)
			{
				return NULL;
			}

			return new Texture;
		}

		IFramebuffer *Renderer::createFramebuffer()
		{
			if(!m_initialized)
			{
				return NULL;
			}

			return new Framebuffer;
		}

		void Renderer::destroyMesh(IMesh *mesh)
		{
			if(!m_initialized)
			{
				return;
			}

			delete (Mesh *)mesh;
		}

		void Renderer::destroyShader(IShader *shader)
		{
			if(!m_initialized)
			{
				return;
			}

			delete (Shader *)shader;
		}

		void Renderer::destroyTexture(ITexture *texture)
		{
			if(!m_initialized)
			{
				return;
			}

			delete (Texture *)texture;
		}

		void Renderer::destroyFramebuffer(IFramebuffer *framebuffer)
		{
			if(!m_initialized)
			{
				return;
			}

			delete (Framebuffer *)framebuffer;
		}

		bool Renderer::update()
		{
			if(!m_initialized)
			{
				return false;
			}

			int width, height;
			getWindow()->getSize(&width, &height);

			if((width != m_lastWidth) || (height != m_lastHeight))
			{
				glViewport(0, 0, width, height);
			}

			return true;
		}

		void Renderer::enableFeature(Feature_t feature)
		{
			if(!m_initialized)
			{
				return;
			}

			GLenum capability = getFeature(feature);
			if(!capability)
			{
				return;
			}

			glEnable(capability);
		}

		void Renderer::disableFeature(Feature_t feature)
		{
			if(!m_initialized)
			{
				return;
			}

			GLenum capability = getFeature(feature);
			if(!capability)
			{
				return;
			}

			glDisable(capability);
		}

		void Renderer::setCullFace(CullFace_t cullFace)
		{
			if(!m_initialized)
			{
				return;
			}

			GLenum mode = getCullFace(cullFace);
			if(!mode)
			{
				return;
			}

			glCullFace(mode);
		}

		void Renderer::setBlendFunction(BlendFunction_t sourceFunction, BlendFunction_t destinationFunction)
		{
			if(!m_initialized)
			{
				return;
			}

			GLenum sourceFactor = getBlendFunction(sourceFunction);
			GLenum destinationFactor = getBlendFunction(destinationFunction);
			if(!sourceFactor || !destinationFactor)
			{
				return;
			}

			glBlendFunc(sourceFactor, destinationFactor);
		}

		void Renderer::setDepthFunction(CompareFunction_t depthFunction)
		{
			if(!m_initialized)
			{
				return;
			}

			GLenum function = getCompareFunction(depthFunction);
			if(!function)
			{
				return;
			}

			glDepthFunc(function);
		}

		void Renderer::setStencilFunction(CompareFunction_t stencilFunction, int reference, unsigned int mask)
		{
			if(!m_initialized)
			{
				return;
			}

			GLenum function = getCompareFunction(stencilFunction);
			if(!function)
			{
				return;
			}

			glStencilFunc(function, reference, mask);
		}

		void Renderer::setStencilOperation(StencilOperation_t stencilFail, StencilOperation_t depthFail, StencilOperation_t depthPass)
		{
			if(!m_initialized)
			{
				return;
			}

			GLenum sFail = getStencilOperation(stencilFail);
			GLenum zFail = getStencilOperation(depthFail);
			GLenum zPass = getStencilOperation(depthPass);
			if(!sFail || !zFail || !zPass)
			{
				return;
			}

			glStencilOp(sFail, zFail, zPass);
		}

		void Renderer::setColorMask(bool r, bool g, bool b, bool a)
		{
			if(!m_initialized)
			{
				return;
			}

			glColorMask(r, g, b, a);
		}

		void Renderer::setDepthMask(bool depth)
		{
			if(!m_initialized)
			{
				return;
			}

			glDepthMask(depth);
		}

		void Renderer::clear(int buffers, float r, float g, float b, float a)
		{
			if(!m_initialized)
			{
				return;
			}

			GLenum mask = getBuffers(buffers);
			if(!mask)
			{
				return;
			}

			glClearColor(r, g, b, a);
			glClear(mask);
		}

		Renderer *getInternalRenderer()
		{
			static Renderer renderer;
			return &renderer;
		}

		IRenderer *getRenderer()
		{
			return getInternalRenderer();
		}
	}
}