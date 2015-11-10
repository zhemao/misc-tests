#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TEST_SIZE (1 << 16)
#define TEST_ITERS 10000

int main(void)
{
	volatile uint16_t *test;
	uint16_t lfsr1 = 0xACE1u, lfsr2 = 0xB571u, lsb;
	int i;

	printf("Allocating memory\n");
	test = malloc(sizeof(uint16_t) * TEST_SIZE);

	printf("Starting memtest\n");

	for (i = 0; i < TEST_ITERS; i++) {
		test[lfsr1] = lfsr2;
		if (test[lfsr1] != lfsr2)
			fprintf(stderr, "Failed r/w at %p\n", &test[lfsr1]);

		// update lfsrs
		lsb = lfsr1 & 1;
		lfsr1 >>= 1;
		lfsr1 ^= (-lsb) & 0xB400u;
		lsb = lfsr2 & 1;
		lfsr2 >>= 1;
		lfsr2 ^= (-lsb) & 0xB400u;
	}
}
