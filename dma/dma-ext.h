#ifndef __DMA_EXT_H__
#define __DMA_EXT_H__

#define SRC_STRIDE 0
#define DST_STRIDE 1
#define SEGMENT_SIZE 2
#define NSEGMENTS 3
#define RESP_STATUS 4

static inline void dma_set_cr(int crnum, unsigned long value)
{
	asm volatile ("custom0 0, %[addr], %[data], 4" ::
			[addr] "r" (crnum), [data] "r" (value));
}

static inline unsigned long dma_get_cr(int crnum)
{
	unsigned long value;
	asm volatile ("custom0 %[value], %[addr], 0, 5" :
			[value] "=r" (value) : [addr] "r" (crnum));
	return value;
}

static inline void dma_transfer(void *dst, void *src)
{
	asm volatile ("custom0 0, %[dst], %[src], 0" ::
			[dst] "r" (dst), [src] "r" (src));
}

#endif
