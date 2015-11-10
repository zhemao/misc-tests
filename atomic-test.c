#define MSCRATCH 0x340
#define CSR0_BASE (1 << 30)

typedef unsigned long long u64;

int main(void)
{
	volatile u64 *csrs = (volatile u64 *)(CSR0_BASE);
	u64 result, addend;

	addend = 5;
	csrs[MSCRATCH] = 24;

	//for (int i = 0; i < 1000; i++) {
	//	asm volatile ("amoadd.d %0, %1, (%2)" : "=r" (result) :
	//			"r" (addend), "r" (&csrs[MSCRATCH]));
	//}

	for (int i = 0; i < 1000; i++) {
		asm volatile ("lr.d %0, (%1)" : "=r" (result) :
				"r" (&csrs[MSCRATCH]));
		if (result != 24)
			return 0x1000 | result;
		asm volatile ("sc.d %0, %1, (%2)" : "=r" (result) :
				"r" (addend), "r" (&csrs[MSCRATCH]));
		if (result == 0)
			return 1;
	}

	return 0;
}
