#include "util.h"
#include "dataset.h"

#include <stdio.h>
#include <stdlib.h>

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

	printf("starting saxpy benchmark");

	starttime = rdtime();
	for (i = 0; i < X_SIZE; i += Y_SIZE) {
		saxpy(a_data, x_data + i, y_data, Y_SIZE);
	}
	endtime = rdtime();

	printf("saxpy took %lu ticks\n", endtime - starttime);

	return 0;
}
