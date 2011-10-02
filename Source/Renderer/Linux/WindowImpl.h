#ifndef WINDOWIMPL_H
#define WINDOWIMPL_H

#include <X11/Xlib.h>
#include <GL/glx.h>
#include <GL/glxext.h>
#include <Gamma/Renderer/IWindow.h>

namespace Gamma
{
	namespace Renderer
	{
		class WindowImpl : public IWindow
		{
		public:
			WindowImpl();
			~WindowImpl();

			bool create(const char *title, int width, int height, bool vsync, bool fullscreen);
			void destroy();
			bool isCreated() const;

			bool update();
			void display();

			void close();
			bool isClosed() const;

			void setSize(int width, int height);
			void getSize(int *width, int *height) const;
		private:
			bool m_created;
			bool m_closed;
		};

		WindowImpl *getInternalWindow();
	}
}

#endif
