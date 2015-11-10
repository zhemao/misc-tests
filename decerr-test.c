#define BAD_ADDRESS 0x40009000

int main(void)
{
	volatile int *ptr = (volatile int *) BAD_ADDRESS;

	*ptr = 1;

	if (*ptr != 0)
		return 1;

	return 0;
}
