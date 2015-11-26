#include "accel.h"
#include <stdio.h>

char array[256];

int main(void)
{
	printf("%p -> %lx\n", array, translator_virt_to_phys(array));
	return 0;
}
