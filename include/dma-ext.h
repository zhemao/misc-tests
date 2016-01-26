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

static inline void dma_set_segsize(unsigned long segment_size)
{
	asm volatile ("csrw 0x802, %[value]" :: [value] "r" (segment_size));
}

static inline void dma_set_nsegments(unsigned long nsegments)
{
	asm volatile ("csrw 0x803, %[value]" :: [value] "r" (nsegments));
}

static inline void dma_set_src_stride(unsigned long src_stride)
{
	asm volatile ("csrw 0x800, %[value]" :: [value] "r" (src_stride));
}

static inline void dma_set_dst_stride(unsigned long dst_stride)
{
	asm volatile ("csrw 0x801, %[value]" :: [value] "r" (dst_stride));
}

static inline void dma_set_wordsize(unsigned long word_size)
{
	asm volatile ("csrw 0x804, %[value]" :: [value] "r" (word_size));
}

static inline int dma_get_resp_status(void)
{
	int status;
	asm volatile ("csrr 0x805, %[value]" : [value] "=r" (status));
	return status;
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
