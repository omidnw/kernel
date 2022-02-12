#include "stdio.h"

void StandardIO::putChar(FrameBuffer* framebuffer, PSFone_Font* psfone_font, unsignedinteger color, char character, unsignedinteger xOffset, unsignedinteger yOffset)
{
	unsignedinteger* pixelPointer = (unsignedinteger*)framebuffer->BaseAddress;
	char* fontpointer = (char*)psfone_font->glyphBuffer + (character * psfone_font->psfone_HEADER->charactersize);
	for(unsignedlong y = yOffset; y < yOffset + 16; y++)
	{
		for(unsignedlong x = xOffset; x < xOffset + 8; x++)
		{
			if((*fontpointer & (0b10000000 >> (x - xOffset))) > 0)
			{
				*(unsignedinteger*)(pixelPointer + x + (y * framebuffer->PixelsPerScanLine)) = color;
			}
		}
		fontpointer++;
	}
}

void StandardIO::Print(FrameBuffer* framebuffer, PSFone_Font* psfone_font, unsignedinteger color, const char* value)
{
	while(*value != 0)
	{
		putChar(framebuffer, psfone_font, color, *value, CursorPosition.X, CursorPosition.Y);
		CursorPosition.X += 8;
		if(CursorPosition.X + 8 > framebuffer->HorizontalResolution)
		{
			CursorPosition.X = 0;
			CursorPosition.Y += 16;
		}
		value++;
	}
}