#include "library/stdlibrary/stdio.h"

extern "C" void myne(FrameBuffer* MainGOPBuffer, PSFone_Font* psfone_font){

        // unsigned int y = 50;
	// unsigned int BBP = 4; // Bytes per pixel;
	// /*
	// each pixel is four bytes wide because it has
	// a red, green, blue and alpha channel.
	// alpha channel is unused in this framebuffer but it can
	// be useful for when you are blending colors.
	// */

	// for(unsigned int x = 0; x < MainGOPBuffer->VerticalResolution / 2 * BBP; x+=BBP)
	// {
	// 	*(unsigned int*)(x + (y * MainGOPBuffer->PixelsPerScanLine * BBP) + MainGOPBuffer->BaseAddress)= 0xffffffff; // this address settings set all of the channels to 1
	// }

	CursorPosition.X = 0;
	CursorPosition.Y = 0;
	// for(int test = 0; test < 50; test++) // test overflow print line just uncomment this line and add tab before the Print function.
	Print(MainGOPBuffer, psfone_font, 0xffffffff, "Hello, world!");
}