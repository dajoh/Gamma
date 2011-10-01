#include "WindowImpl.h"

#define WINDOW_CLASS "GammaWindowClass"
#define WINDOW_STYLE_WINDOWED (WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU)
#define WINDOW_STYLE_FULLSCRN (WS_POPUP)

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

			// Register the window class.
			if(!registerClass())
			{
				return false;
			}

			// Get the instance handle.
			HINSTANCE instance = GetModuleHandle(NULL);
			if(!instance)
			{
				return false;
			}

			// Convert client size to window size.
			RECT rect = {0, 0, width, height};
			if(!AdjustWindowRect(&rect, WINDOW_STYLE_WINDOWED, FALSE))
			{
				return false;
			}

			// Create a dummy window.
			m_window = CreateWindow(WINDOW_CLASS, "", WINDOW_STYLE_WINDOWED, 0, 0, 1, 1, NULL, NULL, instance, NULL);
			if(!m_window)
			{
				return false;
			}

			// Get the dummy DC.
			m_dc = GetDC(m_window);
			if(!m_dc)
			{
				DestroyWindow(m_window);
				return false;
			}

			PIXELFORMATDESCRIPTOR pixelDescriptor;
			ZeroMemory(&pixelDescriptor, sizeof(PIXELFORMATDESCRIPTOR));
			pixelDescriptor.nSize    = sizeof(PIXELFORMATDESCRIPTOR);
			pixelDescriptor.nVersion = 1;
			pixelDescriptor.dwFlags  = PFD_SUPPORT_OPENGL;

			// Get a dummy pixel format.
			int pixelFormat = ChoosePixelFormat(m_dc, &pixelDescriptor);
			if(!pixelFormat || !SetPixelFormat(m_dc, pixelFormat, &pixelDescriptor))
			{
				ReleaseDC(m_window, m_dc);
				DestroyWindow(m_window);
				return false;
			}

			// Create the dummy context.
			m_context = wglCreateContext(m_dc);
			if(!m_context)
			{
				ReleaseDC(m_window, m_dc);
				DestroyWindow(m_window);
				return false;
			}

			// Switch to the dummy context.
			if(!wglMakeCurrent(m_dc, m_context))
			{
				wglDeleteContext(m_context);
				ReleaseDC(m_window, m_dc);
				DestroyWindow(m_window);
				return false;
			}

			// Get extensions.
			PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
			PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
			PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

			// Destroy all our dummy stuff.
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(m_context);
			ReleaseDC(m_window, m_dc);
			DestroyWindow(m_window);

			// Check if we got all of our extensions.
			if(!wglChoosePixelFormatARB || !wglCreateContextAttribsARB || !wglSwapIntervalEXT)
			{
				return false;
			}

			// Go into fullscreen mode.
			if(fullscreen)
			{
				DEVMODE devMode;
				ZeroMemory(&devMode, sizeof(DEVMODE));
				devMode.dmSize       = sizeof(DEVMODE);
				devMode.dmPelsWidth  = width;
				devMode.dmPelsHeight = height;
				devMode.dmBitsPerPel = 32;
				devMode.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

				if(ChangeDisplaySettings(&devMode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
				{
					return false;
				}

				ShowCursor(FALSE);
			}

			// Set the style.
			m_style = fullscreen ? WINDOW_STYLE_FULLSCRN : WINDOW_STYLE_WINDOWED;

			// Create the real window.
			m_window = CreateWindow(WINDOW_CLASS, title, m_style | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, instance, NULL);
			if(!m_window)
			{
				return false;
			}
			else
			{
				SetWindowLong(m_window, GWL_USERDATA, (LONG)this);
			}

			// Get the window DC.
			m_dc = GetDC(m_window);
			if(!m_dc)
			{
				DestroyWindow(m_window);
				return false;
			}

			int pixelAttribs[] =
			{
				WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
				WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
				WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
				WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
				WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
				WGL_COLOR_BITS_ARB, 24,
				WGL_ALPHA_BITS_ARB, 8,
				WGL_DEPTH_BITS_ARB, 24,
				WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
				WGL_SAMPLES_ARB, 4,
				0
			};

			// Get a pixel format.
			unsigned int pixelFormats;
			wglChoosePixelFormatARB(m_dc, pixelAttribs, NULL, 1, &pixelFormat, &pixelFormats);

			if(!pixelFormats || !SetPixelFormat(m_dc, pixelFormat, NULL))
			{
				ReleaseDC(m_window, m_dc);
				DestroyWindow(m_window);
				return false;
			}

			int contextAttribs[] =
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
				WGL_CONTEXT_MINOR_VERSION_ARB, 3,
				0
			};

			// Create the real context.
			m_context = wglCreateContextAttribsARB(m_dc, NULL, contextAttribs);
			if(!m_context)
			{
				ReleaseDC(m_window, m_dc);
				DestroyWindow(m_window);
				return false;
			}

			// Switch to the real context.
			if(!wglMakeCurrent(m_dc, m_context))
			{
				wglDeleteContext(m_context);
				ReleaseDC(m_window, m_dc);
				DestroyWindow(m_window);
				return false;
			}

			// Enable/disable vsync
			wglSwapIntervalEXT(vsync ? 1 : 0);

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

			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(m_context);
			ReleaseDC(m_window, m_dc);
			DestroyWindow(m_window);

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

			MSG message;
			while(PeekMessage(&message, m_window, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}

			return !m_closed;
		}

		void WindowImpl::display()
		{
			if(!m_created)
			{
				return;
			}

			SwapBuffers(m_dc);
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

			RECT rect = {0, 0, width, height};
			AdjustWindowRect(&rect, m_style | WS_VISIBLE, FALSE);
			SetWindowPos(m_window, NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);
		}

		void WindowImpl::getSize(int *width, int *height) const
		{
			if(!m_created)
			{
				return;
			}

			RECT rect;
			GetClientRect(m_window, &rect);

			if(width)
			{
				*width = rect.right;
			}

			if(height)
			{
				*height = rect.bottom;
			}
		}

		bool WindowImpl::registerClass()
		{
			static bool registered = false;
			if(registered)
			{
				return false;
			}

			WNDCLASSEX windowClass;
			windowClass.cbSize        = sizeof(WNDCLASSEX);
			windowClass.style         = CS_OWNDC;
			windowClass.lpfnWndProc   = windowProc;
			windowClass.cbClsExtra    = 0;
			windowClass.cbWndExtra    = 0;
			windowClass.hInstance     = GetModuleHandle(NULL);
			windowClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
			windowClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
			windowClass.hbrBackground = NULL;
			windowClass.lpszMenuName  = NULL;
			windowClass.lpszClassName = WINDOW_CLASS;
			windowClass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

			if(!RegisterClassEx(&windowClass))
			{
				return false;
			}

			registered = true;
			return true;
		}

		LRESULT WindowImpl::windowProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
		{
			WindowImpl *window = (WindowImpl *)GetWindowLong(windowHandle, GWL_USERDATA);
			if(!window)
			{
				return DefWindowProc(windowHandle, message, wParam, lParam);
			}

			switch(message)
			{
			case WM_CLOSE:
				window->close();
				break;
			default:
				return DefWindowProc(windowHandle, message, wParam, lParam);
			}

			return 0;
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