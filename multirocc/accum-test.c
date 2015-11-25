#include "accel.h"

unsigned long data = 0x3421L;

int main(void)
{
	unsigned long result;

	accum_load(0, &data);
	accum_add(0, 2);

	result = accum_read(0);

	if (result != data + 2)
		return result;

	return 0;
}
