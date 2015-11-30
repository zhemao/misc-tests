#include "accel.h"

char string[64] = "The quick brown fox jumped over the lazy dog";

int main(void)
{
	unsigned long count = count_chars(string + 14, 'o');
	if (count != 3)
		return count + 1;
	return 0;
}
