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
		static inline GLenum getGlFeature(RendererFeature_t feature)
		{
			switch(feature)
			{
			case RendererFeature_Blending:
				return GL_BLEND;
			case RendererFeature_DepthTesting:
				return GL_DEPTH_TEST;
			case RendererFeature_StencilTesting:
				return GL_STENCIL_TEST;
			default:
				return 0;
			}
		}

		static inline GLenum getGlBlendFunction(RendererBlendFunction_t blendFunction)
		{
			switch(blendFunction)
			{
			case RendererBlendFunction_Zero:
				return GL_ZERO;
			case RendererBlendFunction_One:
				return GL_ONE;
			case RendererBlendFunction_SourceColor:
				return GL_SRC_COLOR;
			case RendererBlendFunction_OneMinusSourceColor:
				return GL_ONE_MINUS_SRC_COLOR;
			case RendererBlendFunction_DestinationColor:
				return GL_DST_COLOR;
			case RendererBlendFunction_OneMinusDestinationColor:
				return GL_ONE_MINUS_DST_COLOR;
			case RendererBlendFunction_SourceAlpha:
				return GL_SRC_ALPHA;
			case RendererBlendFunction_OneMinusSourceAlpha:
				return GL_ONE_MINUS_SRC_ALPHA;
			case RendererBlendFunction_DestinationAlpha:
				return GL_DST_ALPHA;
			case RendererBlendFunction_OneMinusDestinationAlpha:
				return GL_ONE_MINUS_DST_ALPHA;
			case RendererBlendFunction_SourceAlphaSaturate:
				return GL_SRC_ALPHA_SATURATE;
			default:
				return 0;
			}
		}

		static inline GLenum getGlBoolFunction(RendererBoolFunction_t boolFunction)
		{
			switch(boolFunction)
			{
			case RendererBoolFunction_Never:
				return GL_NEVER;
			case RendererBoolFunction_Always:
				return GL_ALWAYS;
			case RendererBoolFunction_Equal:
				return GL_EQUAL;
			case RendererBoolFunction_NotEqual:
				return GL_NOTEQUAL;
			case RendererBoolFunction_Less:
				return GL_LESS;
			case RendererBoolFunction_LessOrEqual:
				return GL_LEQUAL;
			case RendererBoolFunction_Greater:
				return GL_GREATER;
			case RendererBoolFunction_GreaterOrEqual:
				return GL_GEQUAL;
			default:
				return 0;
			}
		}

		static inline GLenum getGlStencilOperation(RendererStencilOperation_t stencilOperation)
		{
			switch(stencilOperation)
			{
			case RendererStencilOperation_Keep:
				return GL_KEEP;
			case RendererStencilOperation_Zero:
				return GL_ZERO;
			case RendererStencilOperation_Replace:
				return GL_REPLACE;
			case RendererStencilOperation_Increment:
				return GL_INCR;
			case RendererStencilOperation_IncrementWrap:
				return GL_INCR_WRAP;
			case RendererStencilOperation_Decrement:
				return GL_DECR;
			case RendererStencilOperation_DecrementWrap:
				return GL_DECR_WRAP;
			case RendererStencilOperation_Invert:
				return GL_INVERT;
			default:
				return 0;
			}
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

		void Renderer::enableFeature(RendererFeature_t feature)
		{
			if(!m_initialized)
			{
				return;
			}

			GLenum capability = getGlFeature(feature);
			if(!capability)
			{
				return;
			}

			glEnable(capability);
		}

		void Renderer::disableFeature(RendererFeature_t feature)
		{
			if(!m_initialized)
			{
				return;
			}

			GLenum capability = getGlFeature(feature);
			if(!capability)
			{
				return;
			}

			glDisable(capability);
		}

		void Renderer::setBlendFunction(RendererBlendFunction_t sourceFunction, RendererBlendFunction_t destinationFunction)
		{
			if(!m_initialized)
			{
				return;
			}

			GLenum sourceFactor = getGlBlendFunction(sourceFunction);
			GLenum destinationFactor = getGlBlendFunction(destinationFunction);
			if(!sourceFactor || !destinationFactor)
			{
				return;
			}

			glBlendFunc(sourceFactor, destinationFactor);
		}

		void Renderer::setDepthFunction(RendererBoolFunction_t depthFunction)
		{
			if(!m_initialized)
			{
				return;
			}

			GLenum function = getGlBoolFunction(depthFunction);
			if(!function)
			{
				return;
			}

			glDepthFunc(function);
		}

		void Renderer::setStencilFunction(RendererBoolFunction_t stencilFunction, int reference, unsigned int mask)
		{
			if(!m_initialized)
			{
				return;
			}

			GLenum function = getGlBoolFunction(stencilFunction);
			if(!function)
			{
				return;
			}

			glStencilFunc(function, reference, mask);
		}

		void Renderer::setStencilOperation(RendererStencilOperation_t stencilFail, RendererStencilOperation_t depthFail, RendererStencilOperation_t pass)
		{
			if(!m_initialized)
			{
				return;
			}

			GLenum sFail = getGlStencilOperation(stencilFail);
			GLenum zFail = getGlStencilOperation(depthFail);
			GLenum zPass = getGlStencilOperation(pass);
			if(!sFail || !zFail || !zPass)
			{
				return;
			}

			glStencilOp(sFail, zFail, zPass);
		}

		void Renderer::clear(float r, float g, float b, float a)
		{
			if(!m_initialized)
			{
				return;
			}

			glClearColor(r, g, b, a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
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