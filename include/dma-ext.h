#ifndef __DMA_EXT_H__
#define __DMA_EXT_H__

#define SRC_STRIDE 0
#define DST_STRIDE 1
#define SEGMENT_SIZE 2
#define NSEGMENTS 3
#define WORD_SIZE 4
#define RESP_STATUS 5

#define WSZ_BYTE  0
#define WSZ_SHORT 1
#define WSZ_INT 2
#define WSZ_LONG 3

static inline void dma_set_cr(int crnum, unsigned long value)
{
	asm volatile ("custom2 0, %[addr], %[data], 8" ::
			[addr] "r" (crnum), [data] "r" (value));
}

static inline unsigned long dma_get_cr(int crnum)
{
	unsigned long value;
	asm volatile ("custom2 %[value], %[addr], 0, 9" :
			[value] "=r" (value) : [addr] "r" (crnum));
	return value;
}

static inline void dma_transfer(void *dst, void *src)
{
	asm volatile ("custom2 0, %[dst], %[src], 0" ::
			[dst] "r" (dst), [src] "r" (src));
}

static inline void dma_read_prefetch(void *dst)
{
	asm volatile ("custom2 0, %[dst], 0, 2" :: [dst] "r" (dst));
}

static inline void dma_write_prefetch(void *dst)
{
	asm volatile ("custom2 0, %[dst], 0, 3" :: [dst] "r" (dst));
}

static inline void dma_stream_in(void *dst, void *src)
{
	asm volatile ("custom2 0, %[dst], %[src], 4" ::
			[dst] "r" (dst), [src] "r" (src));
}

static inline void dma_stream_out(void *dst, void *src)
{
	asm volatile ("custom2 0, %[dst], %[src], 5" ::
			[dst] "r" (dst), [src] "r" (src));
}

#endif
