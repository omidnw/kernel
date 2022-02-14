#ifndef ADERINA_LIBRARY_STANDARDIO_STRUCTURE
#define ADERINA_LIBRARY_STANDARDIO_STRUCTURE
#pragma once

#include <stddef.h>
#include "../types/numbers.h"
#include "../types/strings.h"

struct FrameBuffer{
	void* BaseAddress;
	size_t BufferSize;
	unsignedinteger HorizontalResolution;
	unsignedinteger VerticalResolution;
	unsignedinteger PixelsPerScanLine;
};

// font struct.

struct PSFone_HEADER{
	unsignedcharacter fontidentifier[2]; // magic array.
	unsignedcharacter fontmode; // font mode.
	unsignedcharacter charactersize; // size of character

};

struct PSFone_Font{
	PSFone_HEADER* psfone_HEADER;
	void* glyphBuffer;
};

struct Point{
	unsignedinteger X;
	unsignedinteger Y;
};

struct StandardIODV{
	struct FrameBuffer* framebuffer;
	struct PSFone_Font* psfone_font;
	unsignedinteger color;
	struct Point CursorPosition;
};

// finish

#endif