#ifndef __UTIL_H__
#define __UTIL_H__

static inline unsigned long rdtime(void) {
	unsigned long timeval;
	asm volatile ("rdtime %[timeval]\n" : [timeval] "=r" (timeval));
	return timeval;
}

static inline unsigned long rdcycle(void) {
	unsigned long cycles;
	asm volatile ("rdcycle %[cycles]\n" : [cycles] "=r" (cycles));
	return cycles;
}

#endif
