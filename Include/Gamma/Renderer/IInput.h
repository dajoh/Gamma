#ifndef GAMMA_RENDERER_IINPUT_H
#define GAMMA_RENDERER_IINPUT_H

#include "Platform.h"
#include "KeyCode.h"
#include "MouseCode.h"

namespace Gamma
{
	namespace Renderer
	{
		class IInput
		{
		public:
			virtual bool initialize() = 0;
			virtual void uninitialize() = 0;
			virtual bool isInitialized() const = 0;

			virtual bool update() = 0;

			virtual bool isKeyUp(KeyCode_t keyCode) const = 0;
			virtual bool isKeyDown(KeyCode_t keyCode) const = 0;
			virtual bool wasKeyPressed(KeyCode_t keyCode) const = 0;

			virtual void setCursorPosition(int x, int y) = 0;
			virtual void getCursorPosition(int *x, int *y) const = 0;

			virtual bool isMouseUp(MouseCode_t mouseCode) const = 0;
			virtual bool isMouseDown(MouseCode_t mouseCode) const = 0;
			virtual bool wasMouseClicked(MouseCode_t mouseCode) const = 0;
		};
		
		GAMMA_RENDERER_EXPORT IInput *getInput();
	}
}

#endif