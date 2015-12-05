#define MSCRATCH 0x340
#define CSR0_BASE ((1 << 30) | (1 << 15))
#define SCR_BASE ((1 << 30) | (1 << 16))

#define NCORES 1
#define MEM_MB (CSR0_BASE >> 20)

typedef unsigned long long u64;

#define TEST_CONST 0x245

int main(void)
{
	volatile u64 *csrs = (volatile u64 *)(CSR0_BASE);
	volatile u64 *scrs = (volatile u64 *)(SCR_BASE);
	u64 value = TEST_CONST;

	asm volatile ("csrw mscratch, %[value]" : : [value] "r" (value));

	value = csrs[MSCRATCH];
	if (value != TEST_CONST)
		return 0x1000 | value;

	value += 1;
	asm volatile ("csrw mscratch, %[value]" : : [value] "r" (value));

	value = csrs[MSCRATCH];
	if (value != TEST_CONST + 1)
		return 0x1000 | value;

	csrs[MSCRATCH] = TEST_CONST + 2;

	asm volatile ("fence");
	asm volatile ("csrr %[value], mscratch" : [value] "=r" (value));

	if (value != TEST_CONST + 2)
		return 0x2000 | value;

	value = scrs[0];
	if (value != NCORES) {
		return 0x3000 | value;
	}

	value = scrs[1];
	if (value != MEM_MB) {
		return 0x4000 | value;
	}

	return 0;
}
