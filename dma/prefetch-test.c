#include "dma-ext.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

#define TEST_SIZE 4096

unsigned long read_block(char *data)
{
	unsigned long start, end;
	char value;

	start = rdtime();
	for (int i = 0; i < TEST_SIZE; i++) {
		value = data[i];
		if (value != 0)
			return -1;
	}
	end = rdtime();

	return end - start;
}

unsigned long write_block(char *data)
{
	unsigned long start, end;

	start = rdtime();
	for (int i = 0; i < TEST_SIZE; i++)
		data[i] = (i & 0xff);
	end = rdtime();

	return end - start;
}

int main(void)
{
	void *rd_section = NULL, *wr_section = NULL;
	unsigned long time;

	rd_section = malloc(2 * TEST_SIZE);
	wr_section = malloc(2 * TEST_SIZE);

	dma_set_cr(SEGMENT_SIZE, TEST_SIZE);
	dma_set_cr(NSEGMENTS, 1);
	dma_set_cr(SRC_STRIDE, 0);
	dma_set_cr(DST_STRIDE, 0);

	dma_read_prefetch(rd_section);
	time = read_block((char *) rd_section + TEST_SIZE);
	printf("Took %ld ticks to read non-prefetched section\n", time);
	time = read_block((char *) rd_section);
	printf("Took %ld ticks to read prefetched section\n", time);

	dma_write_prefetch(wr_section);
	time = write_block(wr_section + TEST_SIZE);
	printf("Took %ld ticks to write non-prefetched section\n", time);
	time = write_block(wr_section);
	printf("Took %ld ticks to write prefetched section\n", time);

	return 0;
}
