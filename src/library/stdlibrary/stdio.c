#include "stdio.h"

Point CursorPosition;

void putChar(FrameBuffer* framebuffer, PSFone_Font* psfone_font, uniinteger color, char character, uniinteger xOffset, uniinteger yOffset)
{
	uniinteger* pixelPointer = (uniinteger*)framebuffer->BaseAddress;
	char* fontpointer = psfone_font->glyphBuffer + (character * psfone_font->psfone_HEADER->charactersize);
	for(unilong y = yOffset; y < yOffset + 16; y++)
	{
		for(unilong x = xOffset; x < xOffset + 8; x++)
		{
			if((*fontpointer & (0b10000000 >> (x - xOffset))) > 0)
			{
				*(uniinteger*)(pixelPointer + x + (y * framebuffer->PixelsPerScanLine)) = color;
			}
		}
		fontpointer++;
	}
}

void Print(FrameBuffer* framebuffer, PSFone_Font* psfone_font, uniinteger color, string value)
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