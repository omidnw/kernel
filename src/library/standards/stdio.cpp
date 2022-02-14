#include "stdio.h"

void System::StandardIO::putChar(char character, unsignedinteger xOffset, unsignedinteger yOffset)
{
	unsignedinteger* pixelPointer = (unsignedinteger*)defaultvalue.framebuffer->BaseAddress;
	char* fontpointer = (char*)defaultvalue.psfone_font->glyphBuffer + (character * defaultvalue.psfone_font->psfone_HEADER->charactersize);
	for(unsignedlong y = yOffset; y < yOffset + 16; y++)
	{
		for(unsignedlong x = xOffset; x < xOffset + 8; x++)
		{
			if((*fontpointer & (0b10000000 >> (x - xOffset))) > 0)
			{
				*(unsignedinteger*)(pixelPointer + x + (y * defaultvalue.framebuffer->PixelsPerScanLine)) = defaultvalue.color;
			}
		}
		fontpointer++;
	}
}

void System::StandardIO::Print(const char* value)
{
	while(*value != 0)
	{
		putChar(*value, defaultvalue.CursorPosition.X, defaultvalue.CursorPosition.Y);
		defaultvalue.CursorPosition.X += 8;
		if(defaultvalue.CursorPosition.X + 8 > defaultvalue.framebuffer->HorizontalResolution)
		{
			defaultvalue.CursorPosition.X = 0;
			defaultvalue.CursorPosition.Y += 16;
		}
		value++;
	}
}