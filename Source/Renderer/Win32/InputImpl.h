#ifndef INPUT_H
#define INPUT_H

#include <Gamma/Renderer/IInput.h>

namespace Gamma
{
	namespace Renderer
	{
		class InputImpl : public IInput
		{
		public:
			InputImpl();
			~InputImpl();

			bool initialize();
			void uninitialize();
			bool isInitialized() const;

			bool update();
			void updateKeys();

			bool isKeyUp(KeyCode_t keyCode) const;
			bool isKeyDown(KeyCode_t keyCode) const;
			bool wasKeyPressed(KeyCode_t keyCode) const;

			void setCursorPosition(int x, int y);
			void getCursorPosition(int *x, int *y) const;

			bool isMouseUp(MouseCode_t mouseCode) const;
			bool isMouseDown(MouseCode_t mouseCode) const;
			bool wasMouseClicked(MouseCode_t mouseCode) const;
		private:
			bool m_initialized;
			bool m_keyUp[KeyCode_NumLock + 1];
			bool m_keyDown[KeyCode_NumLock + 1];
			bool m_keyPressed[KeyCode_NumLock + 1];
			bool m_mouseUp[MouseCode_Middle + 1];
			bool m_mouseDown[MouseCode_Middle + 1];
			bool m_mouseClicked[MouseCode_Middle + 1];

			friend class WindowImpl;
		};

		InputImpl *getInternalInput();
	}
}

#endif