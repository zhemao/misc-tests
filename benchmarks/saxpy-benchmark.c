#include "util.h"
#include "dataset.h"

#include <stdio.h>
#include <stdlib.h>

#define A 47

void saxpy(float a, float *x, float *y, int n)
{
	int i;

	for (i = 0; i < n; i++)
		y[i] += a * x[i];
}

int main(int argc, char *argv[])
{
	int i;
	unsigned long starttime, endtime;
	int yn = INPUT0_SIZE, xn = INPUT1_SIZE;
	float *y = input0_data, *x = input1_data;

	printf("starting saxpy benchmark yn = %d, xn = %d\n", yn, xn);

	starttime = rdtime();
	for (i = 0; i < xn; i += yn) {
		saxpy(A, x + i, y, yn);
	}
	endtime = rdtime();

	printf("saxpy took %lu ticks\n", endtime - starttime);

	return 0;
}
