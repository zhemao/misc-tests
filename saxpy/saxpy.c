#include "util.h"
#include "dataset.h"

#include <stdio.h>
#include <stdlib.h>

#define TOL 0.0000001

void saxpy(float a, float *x, float *y, int n)
{
	int i;

	for (i = 0; i < n; i++)
		y[i] += a * x[i];
}

int check_result(float *res, float *check, int n)
{
	int i;
	float dist;

	for (i = 0; i < n; i++) {
		dist = res[i] - check[i];
		dist = dist * dist;
		if (dist > TOL)
			return -1;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	unsigned long starttime, endtime;

	printf("starting saxpy benchmark\n");

	starttime = rdtime();
	saxpy(input_data_a, input_data_X, input_data_Y, DATA_SIZE);
	endtime = rdtime();

	if (check_result(input_data_Y, verify_data, DATA_SIZE)) {
		fprintf(stderr, "results do not match expected\n");
		exit(EXIT_FAILURE);
	}

	printf("saxpy took %lu ticks\n", endtime - starttime);

	return 0;
}
