#include "dma-ext.h"
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 64

int main(void)
{
	void *rd_section = NULL, *wr_section = NULL;

	posix_memalign(&rd_section, BLOCK_SIZE, 4 * BLOCK_SIZE);
	posix_memalign(&wr_section, BLOCK_SIZE, 4 * BLOCK_SIZE);

	dma_set_cr(SEGMENT_SIZE, BLOCK_SIZE);
	dma_set_cr(NSEGMENTS, 2);
	dma_set_cr(DST_STRIDE, BLOCK_SIZE);

	dma_read_prefetch(rd_section);
	dma_write_prefetch(wr_section);
}
