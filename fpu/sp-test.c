int main(void)
{
	asm volatile ("custom3 0, 0, 0, 0");
	asm volatile ("fence");
	return 0;
}
