#ifndef WINDOWIMPL_H
#define WINDOWIMPL_H

#include <Windows.h>
#include <GL/gl.h>
#include <GL/wglext.h>
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
			static bool registerClass();
			static LRESULT WINAPI windowProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);

			bool m_created;
			bool m_closed;
			DWORD m_style;
			HWND m_window;
			HDC m_dc;
			HGLRC m_context;

			int m_virtualKeyMap[256];
		};

		WindowImpl *getInternalWindow();
	}
}

#endif