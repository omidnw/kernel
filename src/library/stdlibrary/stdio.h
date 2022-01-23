#include "../initializer/initializer.h"

#ifndef ADERINA_LIBRARY_STANDARD_INPUT_OUTPUT
#define ADERINA_LIBRARY_STANDARD_INPUT_OUTPUT

extern Point CursorPosition;
extern void putChar(FrameBuffer* framebuffer, PSFone_Font* psfone_font, uniinteger color, char character, uniinteger xOffset, uniinteger yOffset);
extern void Print(FrameBuffer* framebuffer, PSFone_Font* psfone_font, uniinteger color, string value);

#endif