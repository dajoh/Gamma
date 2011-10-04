#ifndef TGALOADER_H
#define TGALOADER_H

namespace Gamma
{
	namespace Engine
	{
		typedef enum
		{
			TgaFormat_G8,
			TgaFormat_R8G8B8,
			TgaFormat_R8G8B8A8,
		} TgaFormat_t;

		class TgaLoader
		{
		public:
			TgaLoader();
			~TgaLoader();

			bool load(const char *fileName);
			void unload();
			bool isLoaded() const;

			TgaFormat_t getFormat() const;
			unsigned int getWidth() const;
			unsigned int getHeight() const;
			unsigned int getSize() const;

			const void *getData() const;
		private:
			void swizzle();
			void flipVertical();

			bool m_loaded;
			TgaFormat_t m_format;
			unsigned int m_width;
			unsigned int m_height;
			unsigned int m_size;
			unsigned char *m_data;
		};
	}
}

#endif