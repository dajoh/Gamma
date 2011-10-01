#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "TgaLoader.h"

#define TGA_FLAG_VERTICAL_FLIP   (0x20)
#define TGA_FLAG_HORIZONTAL_FLIP (0x10)

#pragma pack(push, 1)
typedef struct
{
	unsigned char identsize;
	unsigned char colormaptype;
	unsigned char imagetype;
	unsigned short colormapstart;
	unsigned short colormaplength;
	unsigned char colormapbits;
	unsigned short x;
	unsigned short y;
	unsigned short width;
	unsigned short height;
	unsigned char bpp;
	unsigned char descriptor;
} TgaHeader_t;
#pragma pack(pop)

TgaLoader::TgaLoader() : m_loaded(false)
{

}

TgaLoader::~TgaLoader()
{
	if(m_loaded)
	{
		unload();
	}
}

bool TgaLoader::load(const char *fileName)
{
	if(m_loaded)
	{
		return false;
	}

	FILE *file = fopen(fileName, "rb");
	if(!file)
	{
		return false;
	}

	TgaHeader_t tgaHeader;
	if(fread(&tgaHeader, 1, sizeof(TgaHeader_t), file) != sizeof(TgaHeader_t))
	{
		fclose(file);
		return false;
	}

	if(tgaHeader.colormaptype != 0 || (tgaHeader.imagetype != 2 && tgaHeader.imagetype != 3))
	{
		fclose(file);
		return false;
	}

	if(tgaHeader.bpp == 8)
	{
		m_format = TgaFormat_G8;
	}
	else if(tgaHeader.bpp == 24)
	{
		m_format = TgaFormat_R8G8B8;
	}
	else if(tgaHeader.bpp == 32)
	{
		m_format = TgaFormat_R8G8B8A8;
	}
	else
	{
		fclose(file);
		return false;
	}

	m_width = tgaHeader.width;
	m_height = tgaHeader.height;
	m_size = (tgaHeader.width * tgaHeader.height) * (tgaHeader.bpp / 8);
	m_data = (unsigned char *)malloc(m_size);

	if(fread(m_data, 1, m_size, file) != m_size)
	{
		free(m_data);
		fclose(file);
		return false;
	}

	if(m_format == TgaFormat_R8G8B8 || m_format == TgaFormat_R8G8B8A8)
	{
		swizzle();
	}

	if(tgaHeader.descriptor & TGA_FLAG_VERTICAL_FLIP)
	{
		flipVertical();
	}

	fclose(file);
	m_loaded = true;
	return true;
}

void TgaLoader::unload()
{
	if(!m_loaded)
	{
		return;
	}

	m_loaded = false;
	free(m_data);
}

bool TgaLoader::isLoaded() const
{
	return m_loaded;
}

TgaFormat_t TgaLoader::getFormat() const
{
	if(!m_loaded)
	{
		return TgaFormat_G8;
	}

	return m_format;
}

unsigned int TgaLoader::getWidth() const
{
	if(!m_loaded)
	{
		return 0;
	}

	return m_width;
}

unsigned int TgaLoader::getHeight() const
{
	if(!m_loaded)
	{
		return 0;
	}

	return m_height;
}

unsigned int TgaLoader::getSize() const
{
	if(!m_loaded)
	{
		return 0;
	}

	return m_size;
}

const void *TgaLoader::getData() const
{
	if(!m_loaded)
	{
		return NULL;
	}

	return m_data;
}

void TgaLoader::swizzle()
{
	int bytesPerPixel;
	switch(m_format)
	{
	case TgaFormat_R8G8B8:
		bytesPerPixel = 3;
		break;
	case TgaFormat_R8G8B8A8:
		bytesPerPixel = 4;
		break;
	}

	for(unsigned int i = 0; i < m_size; i += bytesPerPixel)
	{
		m_data[i] ^= m_data[i + 2] ^= m_data[i] ^= m_data[i + 2];
	}
}

void TgaLoader::flipVertical()
{
	int rowSize;
	switch(m_format)
	{
	case TgaFormat_G8:
		rowSize = 1 * m_width;
		break;
	case TgaFormat_R8G8B8:
		rowSize = 3 * m_width;
		break;
	case TgaFormat_R8G8B8A8:
		rowSize = 4 * m_width;
		break;
	}

	unsigned char *flipped = (unsigned char *)malloc(m_size);
	for(unsigned int i = 0; i < m_height; i++)
	{
		memcpy(&flipped[i * rowSize], &m_data[(m_height - 1 - i) * rowSize], rowSize);
	}

	free(m_data);
	m_data = flipped;
}