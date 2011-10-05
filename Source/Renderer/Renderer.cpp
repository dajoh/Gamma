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

		void Renderer::enableDepthTesting()
		{
			glEnable(GL_DEPTH_TEST);
		}

		void Renderer::disableDepthTesting()
		{
			glDisable(GL_DEPTH_TEST);
		}

		void Renderer::enableBlending()
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		void Renderer::disableBlending()
		{
			glDisable(GL_BLEND);
		}

		void Renderer::clear(float r, float g, float b, float a)
		{
			if(!m_initialized)
			{
				return;
			}

			glClearColor(r, g, b, a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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