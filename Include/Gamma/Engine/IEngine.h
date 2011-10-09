#ifndef GAMMA_ENGINE_IENGINE_H
#define GAMMA_ENGINE_IENGINE_H

#include "Platform.h"
#include "IMatrixStack.h"
#include "ISound.h"
#include "IModel.h"
#include "IImage.h"

namespace Gamma
{
	namespace Engine
	{
		class IEngine
		{
		public:
			virtual bool initialize() = 0;
			virtual void uninitialize() = 0;
			virtual bool isInitialized() const = 0;
			
			virtual IMatrixStack *createMatrixStack() = 0;
			virtual ISound *createSound() = 0;
			virtual IModel *createModel() = 0;
			virtual IImage *createImage() = 0;

			virtual void destroyMatrixStack(IMatrixStack *matrixStack) = 0;
			virtual void destroySound(ISound *sound) = 0;
			virtual void destroyModel(IModel *model) = 0;
			virtual void destroyImage(IImage *image) = 0;

			virtual bool update() = 0;

			virtual void beginFrame() = 0;
			virtual void endFrame() = 0;
			virtual float getEngineTime() const = 0;
			virtual float getFrameTime() const = 0;
		};
		
		GAMMA_ENGINE_EXPORT IEngine *getEngine();
	}
}

#endif