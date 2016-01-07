#include "dma-ext.h"

#define STREAM_LOOPBACK_BASE ((1 << 30) | (1 << 29))
#define TEST_SIZE 52
#define ARRAY_SIZE 64

unsigned long source[ARRAY_SIZE];
unsigned long dest[ARRAY_SIZE];

int main(void)
{
	int i;
	void *stream_base = (void *) STREAM_LOOPBACK_BASE;

	for (i = 0; i < ARRAY_SIZE; i++)
		source[i] = i * 4;

	dma_set_cr(SRC_STRIDE, 0);
	dma_set_cr(DST_STRIDE, 0);
	dma_set_cr(SEGMENT_SIZE, TEST_SIZE * sizeof(long));
	dma_set_cr(NSEGMENTS, 1);
	dma_set_cr(WORD_SIZE, WSZ_LONG);

	dma_stream_out(stream_base, source);
	dma_stream_in(dest, stream_base);
	asm volatile ("fence");

	for (i = 0; i < TEST_SIZE; i++) {
		if (source[i] != dest[i])
			return i + 1;
	}

	for (i = TEST_SIZE; i < ARRAY_SIZE; i++) {
		if (dest[i] != 0)
			return i + 1;
	}

	return 0;
}
