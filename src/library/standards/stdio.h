#ifndef ADERINA_LIBRARY_STANDARD_INPUT_OUTPUT
#define ADERINA_LIBRARY_STANDARD_INPUT_OUTPUT
#pragma once

#include "../structures/standardiostructure.h"


class StandardIO{
    public:
    Point CursorPosition;
    void putChar(FrameBuffer* framebuffer, PSFone_Font* psfone_font, unsignedinteger color, char character, unsignedinteger xOffset, unsignedinteger yOffset);
    void Print(FrameBuffer* framebuffer, PSFone_Font* psfone_font, unsignedinteger color,  const char* value);
};

#endif