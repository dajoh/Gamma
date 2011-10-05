#include <cstring>
#include <Windows.h>
#include <Gamma/Utilities/Debug.h>
#include <Gamma/Renderer/IWindow.h>
#include "InputImpl.h"

namespace Gamma
{
	namespace Renderer
	{
		InputImpl::InputImpl() : m_initialized(false)
		{

		}

		InputImpl::~InputImpl()
		{
			if(m_initialized)
			{
				uninitialize();
			}
		}

		bool InputImpl::initialize()
		{
			if(m_initialized || !getWindow()->isCreated())
			{
				return false;
			}

			memset(m_keyUp, 1, sizeof(bool) * (KeyCode_NumLock + 1));
			memset(m_keyDown, 0, sizeof(bool) * (KeyCode_NumLock + 1));
			memset(m_keyPressed, 0, sizeof(bool) * (KeyCode_NumLock + 1));
			memset(m_mouseUp, 1, sizeof(bool) * (MouseCode_Middle + 1));
			memset(m_mouseDown, 0, sizeof(bool) * (MouseCode_Middle + 1));
			memset(m_mouseClicked, 0, sizeof(bool) * (MouseCode_Middle + 1));

			m_initialized = true;
			return true;
		}

		void InputImpl::uninitialize()
		{
			if(!m_initialized)
			{
				return;
			}

			m_initialized = false;
		}

		bool InputImpl::isInitialized() const
		{
			return m_initialized;
		}

		bool InputImpl::update()
		{
			if(!m_initialized)
			{
				return false;
			}

			return true;
		}

		void InputImpl::updateKeys()
		{
			if(!m_initialized)
			{
				return;
			}

			memset(m_keyPressed, 0, sizeof(bool) * (KeyCode_NumLock + 1));
			memset(m_mouseClicked, 0, sizeof(bool) * (MouseCode_Middle + 1));
		}

		bool InputImpl::isKeyUp(KeyCode_t keyCode) const
		{
			if(!m_initialized)
			{
				return false;
			}

			return m_keyUp[keyCode];
		}

		bool InputImpl::isKeyDown(KeyCode_t keyCode) const
		{
			if(!m_initialized)
			{
				return false;
			}

			return m_keyDown[keyCode];
		}

		bool InputImpl::wasKeyPressed(KeyCode_t keyCode) const
		{
			if(!m_initialized)
			{
				return false;
			}

			return m_keyPressed[keyCode];
		}

		void InputImpl::setCursorPosition(int x, int y)
		{
			if(!m_initialized)
			{
				return;
			}

			SetCursorPos(x, y);
		}

		void InputImpl::getCursorPosition(int *x, int *y) const
		{
			if(!m_initialized)
			{
				return;
			}

			POINT point;
			GetCursorPos(&point);

			if(x)
			{
				*x = point.x;
			}

			if(y)
			{
				*y = point.y;
			}
		}

		bool InputImpl::isMouseUp(MouseCode_t mouseCode) const
		{
			if(!m_initialized)
			{
				return false;
			}

			return m_mouseUp[mouseCode];
		}

		bool InputImpl::isMouseDown(MouseCode_t mouseCode) const
		{
			if(!m_initialized)
			{
				return false;
			}

			return m_mouseDown[mouseCode];
		}

		bool InputImpl::wasMouseClicked(MouseCode_t mouseCode) const
		{
			if(!m_initialized)
			{
				return false;
			}

			return m_mouseClicked[mouseCode];
		}

		IInput *getInput()
		{
			return getInternalInput();
		}

		InputImpl *getInternalInput()
		{
			static InputImpl input;
			return &input;
		}
	}
}