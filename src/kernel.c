typedef unsigned long long size_t;

typedef struct{
	void* BaseAddress;
	size_t BufferSize;
	unsigned int HorizontalResolution;
	unsigned int VerticalResolution;
	unsigned int PixelsPerScanLine;
} FrameBuffer;

void myne(FrameBuffer* MainGOPBuffer){

        unsigned int y = 50;
	unsigned int BBP = 4; // Bytes per pixel;
	/*
	each pixel is four bytes wide because it has
	a red, green, blue and alpha channel.
	alpha channel is unused in this framebuffer but it can
	be useful for when you are blending colors.
	*/

	for(unsigned int x = 0; x < MainGOPBuffer->VerticalResolution / 2 * BBP; x+=BBP)
	{
		*(unsigned int*)(x + (y * MainGOPBuffer->PixelsPerScanLine * BBP) + MainGOPBuffer->BaseAddress)= 0xffffffff; // this address settings set all of the channels to 1
	}

        return 0 ;
}