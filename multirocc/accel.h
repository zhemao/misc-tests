#ifndef __ACCEL_H__
#define __ACCEL_H__

static inline void accum_write(int addr, unsigned long data)
{
	asm volatile ("custom0 0, %[data], %[addr], 0" ::
			[data] "r" (data), [addr] "r" (addr));
}

static inline unsigned long accum_read(int addr)
{
	unsigned long value;
	asm volatile ("custom0 %[value], zero, %[addr], 1" :
			[value] "=r" (value) : [addr] "r" (addr));
	return value;
}

static inline void accum_load(int regaddr, void *memaddr)
{
	asm volatile ("fence");
	asm volatile ("custom0 0, %[memaddr], %[regaddr], 2" ::
			[memaddr] "r" (memaddr), [regaddr] "r" (regaddr));
}

static inline void accum_add(int addr, unsigned long addend)
{
	asm volatile ("custom0 0, %[addend], %[addr], 3" ::
			[addend] "r" (addend), [addr] "r" (addr));
}

static inline unsigned long translator_virt_to_phys(void *vaddr)
{
	unsigned long paddr;
	asm volatile ("custom1 %[paddr], %[vaddr], 0, 0" :
			[paddr] "=r" (paddr) : [vaddr] "r" (vaddr));
	return paddr;
}

static inline void blockstore_load(void *memaddr)
{
	asm volatile ("fence");
	asm volatile ("custom2 0, %[memaddr], 0, 0" :: [memaddr] "r" (memaddr));
}

static inline void blockstore_flush(void *memaddr)
{
	asm volatile ("custom2 0, %[memaddr], 0, 1" :: [memaddr] "r" (memaddr));
	asm volatile ("fence");
}

static inline unsigned long blockstore_read(int regaddr)
{
	unsigned long value;
	asm volatile ("custom2 %[value], %[regaddr], 0, 2" :
			[value] "=r" (value) : [regaddr] "r" (regaddr));
	return value;
}

static inline void blockstore_write(int regaddr, unsigned long value)
{
	asm volatile ("custom2 0, %[addr], %[value], 3" ::
			[value] "r" (value), [addr] "r" (regaddr));
}

#endif
