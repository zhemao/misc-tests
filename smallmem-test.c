#define SMALLMEM_BASE ((1 << 30) | (1 << 15))

int main(void)
{
	volatile int *smallmem = (volatile int *)(SMALLMEM_BASE);
	int regmem[16];
	int i, error = 0;

	smallmem[3] = 2;
	smallmem[3] = 3;
	smallmem[0] = 1;

	for (i = 0; i < 16; i++)
		regmem[i] = i * 2;

	if (smallmem[3] != 3)
		return 1;

	smallmem[0] = 16;

	if (smallmem[3] != 3)
		return 2;

	if (smallmem[0] != 16)
		return 3;

	for (i = 0; i < 16; i++) {
		if (regmem[i] != i * 2)
			error = 1;
	}

	if (error)
		return 4;

	return 0;
}
