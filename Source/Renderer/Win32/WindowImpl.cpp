#include <Gamma/Utilities/Debug.h>
#include "WindowImpl.h"
#include "InputImpl.h"

#define WINDOW_CLASS "GammaWindowClass"
#define WINDOW_STYLE_WINDOWED (WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU)
#define WINDOW_STYLE_FULLSCRN (WS_POPUP)

namespace Gamma
{
	namespace Renderer
	{
		WindowImpl::WindowImpl() : m_created(false)
		{
			memset(m_virtualKeyMap, 0, sizeof(int) * 256);

			// Mouse buttons.
			m_virtualKeyMap[VK_LBUTTON] = MouseCode_Left;
			m_virtualKeyMap[VK_RBUTTON] = MouseCode_Right;
			m_virtualKeyMap[VK_MBUTTON] = MouseCode_Middle;

			// Number keys.
			m_virtualKeyMap['0'] = KeyCode_0;
			m_virtualKeyMap['1'] = KeyCode_1;
			m_virtualKeyMap['2'] = KeyCode_2;
			m_virtualKeyMap['3'] = KeyCode_3;
			m_virtualKeyMap['4'] = KeyCode_4;
			m_virtualKeyMap['5'] = KeyCode_5;
			m_virtualKeyMap['6'] = KeyCode_6;
			m_virtualKeyMap['7'] = KeyCode_7;
			m_virtualKeyMap['8'] = KeyCode_8;
			m_virtualKeyMap['9'] = KeyCode_9;

			// Letter keys.
			m_virtualKeyMap['A'] = KeyCode_A;
			m_virtualKeyMap['B'] = KeyCode_B;
			m_virtualKeyMap['C'] = KeyCode_C;
			m_virtualKeyMap['D'] = KeyCode_D;
			m_virtualKeyMap['E'] = KeyCode_E;
			m_virtualKeyMap['F'] = KeyCode_F;
			m_virtualKeyMap['G'] = KeyCode_G;
			m_virtualKeyMap['H'] = KeyCode_H;
			m_virtualKeyMap['I'] = KeyCode_I;
			m_virtualKeyMap['J'] = KeyCode_J;
			m_virtualKeyMap['K'] = KeyCode_K;
			m_virtualKeyMap['L'] = KeyCode_L;
			m_virtualKeyMap['M'] = KeyCode_M;
			m_virtualKeyMap['N'] = KeyCode_N;
			m_virtualKeyMap['O'] = KeyCode_O;
			m_virtualKeyMap['P'] = KeyCode_P;
			m_virtualKeyMap['Q'] = KeyCode_Q;
			m_virtualKeyMap['R'] = KeyCode_R;
			m_virtualKeyMap['S'] = KeyCode_S;
			m_virtualKeyMap['T'] = KeyCode_T;
			m_virtualKeyMap['U'] = KeyCode_U;
			m_virtualKeyMap['V'] = KeyCode_V;
			m_virtualKeyMap['W'] = KeyCode_W;
			m_virtualKeyMap['X'] = KeyCode_X;
			m_virtualKeyMap['Y'] = KeyCode_Y;
			m_virtualKeyMap['Z'] = KeyCode_Z;

			// Numpad keys.
			m_virtualKeyMap[VK_NUMPAD0] = KeyCode_Pad0;
			m_virtualKeyMap[VK_NUMPAD1] = KeyCode_Pad1;
			m_virtualKeyMap[VK_NUMPAD2] = KeyCode_Pad2;
			m_virtualKeyMap[VK_NUMPAD3] = KeyCode_Pad3;
			m_virtualKeyMap[VK_NUMPAD4] = KeyCode_Pad4;
			m_virtualKeyMap[VK_NUMPAD5] = KeyCode_Pad5;
			m_virtualKeyMap[VK_NUMPAD6] = KeyCode_Pad6;
			m_virtualKeyMap[VK_NUMPAD7] = KeyCode_Pad7;
			m_virtualKeyMap[VK_NUMPAD8] = KeyCode_Pad8;
			m_virtualKeyMap[VK_NUMPAD9] = KeyCode_Pad9;
			m_virtualKeyMap[VK_DIVIDE] = KeyCode_PadDivide;
			m_virtualKeyMap[VK_MULTIPLY] = KeyCode_PadMultiply;
			m_virtualKeyMap[VK_SUBTRACT] = KeyCode_PadMinus;
			m_virtualKeyMap[VK_ADD] = KeyCode_PadPlus;
			m_virtualKeyMap[VK_RETURN] = KeyCode_PadEnter;
			m_virtualKeyMap[VK_DECIMAL] = KeyCode_PadDecimal;

			// General keys.
			m_virtualKeyMap[0xDB] = KeyCode_LeftBracket;
			m_virtualKeyMap[0xDD] = KeyCode_RightBracket;
			m_virtualKeyMap[0xBA] = KeyCode_Semicolon;
			m_virtualKeyMap[0xDE] = KeyCode_Apostrophe;
			m_virtualKeyMap[0xBC] = KeyCode_Comma;
			m_virtualKeyMap[0xBE] = KeyCode_Period;
			m_virtualKeyMap[0xBF] = KeyCode_Slash;
			m_virtualKeyMap[0xDC] = KeyCode_Backslash;
			m_virtualKeyMap[0xBD] = KeyCode_Minus;
			m_virtualKeyMap[0xBB] = KeyCode_Equal;
			m_virtualKeyMap[VK_RETURN] = KeyCode_Enter;
			m_virtualKeyMap[VK_SPACE] = KeyCode_Space;
			m_virtualKeyMap[VK_BACK] = KeyCode_Backspace;
			m_virtualKeyMap[VK_ESCAPE] = KeyCode_Escape;
			m_virtualKeyMap[VK_TAB] = KeyCode_Tab;
			m_virtualKeyMap[VK_INSERT] = KeyCode_Insert;
			m_virtualKeyMap[VK_HOME] = KeyCode_Home;
			m_virtualKeyMap[VK_DELETE] = KeyCode_Delete;
			m_virtualKeyMap[VK_END] = KeyCode_End;
			m_virtualKeyMap[VK_PRIOR] = KeyCode_PageUp;
			m_virtualKeyMap[VK_NEXT] = KeyCode_PageDown;
			m_virtualKeyMap[VK_SNAPSHOT] = KeyCode_PrintScreen;
			m_virtualKeyMap[VK_PAUSE] = KeyCode_Pause;
			m_virtualKeyMap[VK_LSHIFT] = KeyCode_LeftShift;
			m_virtualKeyMap[VK_RSHIFT] = KeyCode_RightShift;
			m_virtualKeyMap[VK_LCONTROL] = KeyCode_LeftControl;
			m_virtualKeyMap[VK_RCONTROL] = KeyCode_RightControl;
			m_virtualKeyMap[VK_MENU] = KeyCode_LeftAlt;
			m_virtualKeyMap[VK_MENU] = KeyCode_RightAlt;

			// Arrow keys.
			m_virtualKeyMap[VK_UP] = KeyCode_Up;
			m_virtualKeyMap[VK_LEFT] = KeyCode_Left;
			m_virtualKeyMap[VK_DOWN] = KeyCode_Down;
			m_virtualKeyMap[VK_RIGHT] = KeyCode_Right;

			// F keys.
			m_virtualKeyMap[VK_F1] = KeyCode_F1;
			m_virtualKeyMap[VK_F2] = KeyCode_F2;
			m_virtualKeyMap[VK_F3] = KeyCode_F3;
			m_virtualKeyMap[VK_F4] = KeyCode_F4;
			m_virtualKeyMap[VK_F5] = KeyCode_F5;
			m_virtualKeyMap[VK_F6] = KeyCode_F6;
			m_virtualKeyMap[VK_F7] = KeyCode_F7;
			m_virtualKeyMap[VK_F8] = KeyCode_F8;
			m_virtualKeyMap[VK_F9] = KeyCode_F9;
			m_virtualKeyMap[VK_F10] = KeyCode_F10;
			m_virtualKeyMap[VK_F11] = KeyCode_F11;
			m_virtualKeyMap[VK_F12] = KeyCode_F12;

			// Toggle keys.
			m_virtualKeyMap[VK_CAPITAL] = KeyCode_CapsLock;
			m_virtualKeyMap[VK_SCROLL] = KeyCode_ScrollLock;
			m_virtualKeyMap[VK_NUMLOCK] = KeyCode_NumLock;
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
			WindowImpl *window = getInternalWindow();
			InputImpl *input = getInternalInput();

			switch(message)
			{
			case WM_CLOSE:
				window->close();
				return 0;
			}

			if(input->isInitialized())
			{
				if(message == WM_KEYUP || message == WM_KEYDOWN)
				{
					int keyCode = window->m_virtualKeyMap[wParam];
					if(keyCode != KeyCode_None)
					{
						if(message == WM_KEYUP)
						{
							input->m_keyUp[keyCode] = true;
							input->m_keyDown[keyCode] = false;
							input->m_keyPressed[keyCode] = true;
						}
						else
						{
							input->m_keyUp[keyCode] = false;
							input->m_keyDown[keyCode] = true;
						}
					}
				}
			}

			return DefWindowProc(windowHandle, message, wParam, lParam);
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