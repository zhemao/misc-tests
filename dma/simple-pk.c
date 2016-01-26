#include "dma-ext.h"
#include <stdio.h>

#define TEST_SIZE 400

int src_array[TEST_SIZE];
int dst_array[TEST_SIZE];

int main(void)
{
	int i;

	printf("Starting DMA test\n");

	dma_set_segsize(TEST_SIZE * sizeof(int));
	dma_set_nsegments(1);
	dma_set_src_stride(0);
	dma_set_dst_stride(0);

	for (i = 0; i < TEST_SIZE; i++)
		src_array[i] = (i << 16) | i;

	asm volatile ("fence");
	dma_transfer(dst_array, src_array);
	asm volatile ("fence");

	for (i = 0; i < TEST_SIZE; i++) {
		if (dst_array[i] != src_array[i]) {
			printf("Error: expected %d, got %d\n",
				src_array[i], dst_array[i]);
			return -1;
		}
	}

	printf("DMA test complete\n");

	return 0;
}
