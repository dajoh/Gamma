#ifndef GAMMA_RENDERER_IWINDOW_H
#define GAMMA_RENDERER_IWINDOW_H

#include "Platform.h"

namespace Gamma
{
	namespace Renderer
	{
		class IWindow
		{
		public:
			virtual bool create(const char *title, int width, int height, bool vsync, bool fullscreen) = 0;
			virtual void destroy() = 0;
			virtual bool isCreated() const = 0;

			virtual bool update() = 0;
			virtual void display() = 0;

			virtual void close() = 0;
			virtual bool isClosed() const = 0;

			virtual void setSize(int width, int height) = 0;
			virtual void getSize(int *width, int *height) const = 0;
		};
		
		GAMMA_RENDERER_EXPORT IWindow *getWindow();
	}
}

#endif