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

static inline unsigned long count_chars(char *start, char needle)
{
	unsigned long count;
	asm volatile ("fence");
	asm volatile ("custom2 %[count], %[start], %[needle], 0" :
			[count] "=r" (count) :
			[start] "r" (start), [needle] "r" (needle));
	return count;
}

#endif
