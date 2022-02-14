#ifndef ADERINA_LIBRARY_STANDARD_INPUT_OUTPUT
#define ADERINA_LIBRARY_STANDARD_INPUT_OUTPUT
#pragma once

#include "../structures/standardiostructure.h"

namespace System{
    class StandardIO{
        public:
            StandardIODV defaultvalue;
            void putChar(char character, unsignedinteger xOffset, unsignedinteger yOffset);
            void Print(const char* value);
    };
}

#endif