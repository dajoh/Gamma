#ifndef ENGINE_H
#define ENGINE_H

#ifdef GAMMA_PLATFORM_WIN32
#include <Windows.h>
#endif

#include <Gamma/Engine/IEngine.h>

namespace Gamma
{
	namespace Engine
	{
		class Engine : public IEngine
		{
		public:
			Engine();
			~Engine();

			bool initialize();
			void uninitialize();
			bool isInitialized() const;

			IMatrixStack *createMatrixStack();
			ISound *createSound();
			IModel *createModel();
			IImage *createImage();

			void destroyMatrixStack(IMatrixStack *matrixStack);
			void destroySound(ISound *sound);
			void destroyModel(IModel *model);
			void destroyImage(IImage *image);

			bool update();

			void beginFrame();
			void endFrame();
			float getEngineTime() const;
			float getFrameTime() const;
		private:
			bool m_initialized;
			bool m_inFrame;

#ifdef GAMMA_PLATFORM_WIN32
			LARGE_INTEGER m_frequency;
			LARGE_INTEGER m_engineTime;
			LARGE_INTEGER m_frameStartTime;
			LARGE_INTEGER m_frameEndTime;
#else
			// ...
#endif
		};

		Engine *getInternalEngine();
	}
}

#endif