#include "WindowImpl.h"

namespace Gamma
{
	namespace Renderer
	{
		WindowImpl::WindowImpl() : m_created(false)
		{

		}

		WindowImpl::~WindowImpl()
		{
			if(m_created)
			{
				destroy();
			}
		}

		bool WindowImpl::create(const char *title, int width, int height, bool vsync, bool fullscreen)
		{
			if(m_created)
			{
				return false;
			}

			// ...

			m_created = true;
			m_closed = false;
			return true;
		}

		void WindowImpl::destroy()
		{
			if(!m_created)
			{
				return;
			}

			// ...

			m_created = false;
		}

		bool WindowImpl::isCreated() const
		{
			return m_created;
		}

		bool WindowImpl::update()
		{
			if(!m_created)
			{
				return false;
			}

			// ...

			return !m_closed;
		}

		void WindowImpl::display()
		{
			if(!m_created)
			{
				return;
			}

			// ...
		}

		void WindowImpl::close()
		{
			if(!m_created)
			{
				return;
			}

			m_closed = true;
		}

		bool WindowImpl::isClosed() const
		{
			if(!m_created)
			{
				return true;
			}

			return m_closed;
		}

		void WindowImpl::setSize(int width, int height)
		{
			if(!m_created)
			{
				return;
			}

			// ...
		}

		void WindowImpl::getSize(int *width, int *height) const
		{
			if(!m_created)
			{
				return;
			}

			// ...
		}

		WindowImpl *getInternalWindow()
		{
			static WindowImpl window;
			return &window;
		}

		IWindow *getWindow()
		{
			return getInternalWindow();
		}
	}
}
