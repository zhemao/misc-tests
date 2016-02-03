#include "dma-ext.h"
#include <stdint.h>

#define MMIO_BASE (1 << 30)
#define CSR0_BASE ((1 << 30) | (1 << 15))

uint64_t test[128];

int main(void)
{
	int status;

	dma_set_segsize(128);
	dma_set_nsegments(1);
	dma_set_wordsize(WSZ_LONG);

	dma_transfer((void *) MMIO_BASE, test);
	asm volatile ("fence");

	status = dma_get_resp_status();
	if (status != PAGE_FAULT)
		return status;

	dma_transfer((void *) CSR0_BASE, test);
	asm volatile ("fence");

	status = dma_get_resp_status();
	if (status != INVALID_REGION)
		return status;

	dma_read_prefetch((void *) CSR0_BASE);
	asm volatile ("fence");

	status = dma_get_resp_status();
	if (status != INVALID_REGION)
		return status;

	dma_stream_in(test, test);
	asm volatile ("fence");

	status = dma_get_resp_status();
	if (status != INVALID_REGION)
		return status;

	dma_stream_out(test, test);
	asm volatile ("fence");

	status = dma_get_resp_status();
	if (status != INVALID_REGION)
		return status;

	return 0;

}
