#include "dma-ext.h"
#include "util.h"
#include <stdlib.h>

#define TEST_SIZE 256

char rd_section[2 * TEST_SIZE] = {0};
char wr_section[2 * TEST_SIZE] = {0};

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
	unsigned long pf_time, npf_time;

	dma_set_cr(SEGMENT_SIZE, TEST_SIZE);
	dma_set_cr(NSEGMENTS, 1);
	dma_set_cr(SRC_STRIDE, 0);
	dma_set_cr(DST_STRIDE, 0);

	dma_read_prefetch(rd_section);
	asm volatile ("fence");
	pf_time = read_block((char *) rd_section);
	npf_time = read_block((char *) rd_section + TEST_SIZE);
	if (npf_time == -1 || pf_time == -1)
		return 3;
	if (pf_time > npf_time)
		return 1;

	dma_write_prefetch(wr_section);
	asm volatile ("fence");
	pf_time = write_block(wr_section);
	npf_time = write_block(wr_section + TEST_SIZE);
	if (npf_time == -1 || pf_time == -1)
		return 3;
	if (pf_time > npf_time)
		return 2;

	return 0;
}
