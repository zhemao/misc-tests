#include "dataset.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>

int result[DATA_SIZE];

void membw(int *res, int a, int *x, int n)
{
	int i;

	for (i = 0; i < n; i++)
		res[i]= a * x[i];
}

int verify(int *res, int *verify, int n)
{
	int i;

	for (i = 0; i < n; i++)
		if (res[i] != verify[i]) {
			fprintf("data doesn't match at %d\n", i);
			return -1;
		}

	return 0;
}

int main(int argc, char *argv[])
{
	int testn;
	unsigned long start, end;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s n\n", argv[0]);
		return -1;
	}

	testn = atoi(argv[1]);
	start = rdcycle();
	membw(result, input_data_a, input_data_X, testn);
	end = rdcycle();

	printf("time[%d] = %lu\n", testn, end - start);

	return 0;
}
