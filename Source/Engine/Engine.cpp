#include <cstddef>
#include <Gamma/Audio/IAudio.h>
#include <Gamma/Renderer/IInput.h>
#include <Gamma/Renderer/IRenderer.h>
#include "Engine.h"
#include "MatrixStack.h"
#include "Sound.h"
#include "Model.h"
#include "Image.h"

namespace Gamma
{
	namespace Engine
	{
		Engine::Engine() : m_initialized(false)
		{

		}

		Engine::~Engine()
		{
			if(m_initialized)
			{
				uninitialize();
			}
		}

		bool Engine::initialize()
		{
			if(m_initialized || !Audio::getAudio()->isInitialized() || !Renderer::getInput()->isInitialized() || !Renderer::getRenderer()->isInitialized())
			{
				return false;
			}

#ifdef GAMMA_PLATFORM_WIN32
			QueryPerformanceFrequency(&m_frequency);
			QueryPerformanceCounter(&m_engineStartTime);
#else
			// ...
#endif

			m_initialized = true;
			m_inFrame = false;
			return true;
		}

		void Engine::uninitialize()
		{
			if(!m_initialized)
			{
				return;
			}

			m_initialized = false;
		}

		bool Engine::isInitialized() const
		{
			return m_initialized;
		}

		IMatrixStack *Engine::createMatrixStack()
		{
			if(!m_initialized)
			{
				return NULL;
			}

			return new MatrixStack;
		}

		ISound *Engine::createSound()
		{
			if(!m_initialized)
			{
				return NULL;
			}

			return new Sound;
		}

		IModel *Engine::createModel()
		{
			if(!m_initialized)
			{
				return NULL;
			}

			return new Model;
		}

		IImage *Engine::createImage()
		{
			if(!m_initialized)
			{
				return NULL;
			}

			return new Image;
		}

		void Engine::destroyMatrixStack(IMatrixStack *matrixStack)
		{
			if(!m_initialized)
			{
				return;
			}

			delete (MatrixStack *)matrixStack;
		}

		void Engine::destroySound(ISound *sound)
		{
			if(!m_initialized)
			{
				return;
			}

			delete (Sound *)sound;
		}

		void Engine::destroyModel(IModel *model)
		{
			if(!m_initialized)
			{
				return;
			}

			delete (Model *)model;
		}

		void Engine::destroyImage(IImage *image)
		{
			if(!m_initialized)
			{
				return;
			}

			delete (Image *)image;
		}

		bool Engine::update()
		{
			if(!m_initialized)
			{
				return false;
			}

			return true;
		}

		void Engine::beginFrame()
		{
			if(!m_initialized || m_inFrame)
			{
				return;
			}

#ifdef GAMMA_PLATFORM_WIN32
			QueryPerformanceCounter(&m_frameStartTime);
#else
			// ...
#endif

			m_inFrame = true;
		}

		void Engine::endFrame()
		{
			if(!m_initialized || !m_inFrame)
			{
				return;
			}

#ifdef GAMMA_PLATFORM_WIN32
			LARGE_INTEGER currentTime;
			QueryPerformanceCounter(&currentTime);
			m_lastFrameTime = (currentTime.QuadPart - m_frameStartTime.QuadPart) / (float)m_frequency.QuadPart;
#else
			// ...
#endif

			m_inFrame = false;
		}

		float Engine::getEngineTime() const
		{
			if(!m_initialized)
			{
				return 0.0f;
			}

#ifdef GAMMA_PLATFORM_WIN32
			LARGE_INTEGER currentTime;
			QueryPerformanceCounter(&currentTime);
			return (currentTime.QuadPart - m_engineStartTime.QuadPart) / (float)m_frequency.QuadPart;
#else
			return 0.0f;
#endif
		}

		float Engine::getFrameTime() const
		{
			if(!m_initialized)
			{
				return 0.0f;
			}

#ifdef GAMMA_PLATFORM_WIN32
			LARGE_INTEGER currentTime;
			QueryPerformanceCounter(&currentTime);
			return (currentTime.QuadPart - m_frameStartTime.QuadPart) / (float)m_frequency.QuadPart;
#else
			return 0.0f;
#endif
		}

		float Engine::getLastFrameTime() const
		{
			if(!m_initialized)
			{
				return 0.0f;
			}

#ifdef GAMMA_PLATFORM_WIN32
			return m_lastFrameTime;
#else
			return 0.0f;
#endif
		}

		Engine *getInternalEngine()
		{
			static Engine engine;
			return &engine;
		}

		IEngine *getEngine()
		{
			return getInternalEngine();
		}
	}
}