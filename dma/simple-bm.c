#include "dma-ext.h"

#define TEST_SIZE 400

int src_array[TEST_SIZE];
int dst_array[TEST_SIZE];

int main(void)
{
	int i;

	dma_set_cr(SEGMENT_SIZE, TEST_SIZE * sizeof(int));
	dma_set_cr(NSEGMENTS, 1);
	dma_set_cr(SRC_STRIDE, 0);
	dma_set_cr(DST_STRIDE, 0);

	for (i = 0; i < TEST_SIZE; i++)
		src_array[i] = (i << 16) | i;

	asm volatile ("fence");
	dma_transfer(dst_array, src_array);
	asm volatile ("fence");

	for (i = 0; i < TEST_SIZE; i++) {
		if (dst_array[i] != src_array[i])
			return -1;
	}

	return 0;
}
