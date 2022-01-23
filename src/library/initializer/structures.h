#include "typedefinitializer.h"

#ifndef ADERINA_LIBRARY_INITIALIZE_STRUCTURES
#define ADERINA_LIBRARY_INITIALIZE_STRUCTURES

typedef struct{
	void* BaseAddress;
	size_t BufferSize;
	unsigned int HorizontalResolution;
	unsigned int VerticalResolution;
	unsigned int PixelsPerScanLine;
} FrameBuffer;

// font struct.

typedef struct{
	unsigned char fontidentifier[2]; // magic array.
	unsigned char fontmode; // font mode.
	unsigned char charactersize; // size of character

} PSFone_HEADER;

typedef struct{
	PSFone_HEADER* psfone_HEADER;
	void* glyphBuffer;
} PSFone_Font;

typedef struct{
	uniinteger X;
	uniinteger Y;
} Point;

// finish

#endif