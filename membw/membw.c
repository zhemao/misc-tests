#include "dataset.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>

int result[RES_SIZE];

void membw(int *res, int *x, int *k, int n)
{
	int i;

	for (i = 0; i < n; i++)
		res[i] = x[k[i]];
}

int verify(int *res, int *ver, int n)
{
	int i;

	for (i = 0; i < n; i++)
		if (res[i] != ver[i]) {
			fprintf(stderr, "data doesn't match at %d\n", i);
			return -1;
		}

	return 0;
}

int main(int argc, char *argv[])
{
	unsigned long start, end;

	start = rdcycle();
	membw(result, input_data_X, input_data_K, RES_SIZE);
	end = rdcycle();

	printf("time[%d, %d] = %lu\n", DATA_SIZE, RES_SIZE, end - start);

	return verify(result, verify_data, RES_SIZE);
}
