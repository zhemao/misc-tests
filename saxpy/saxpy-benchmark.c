#include "util.h"
#include "dataset.h"
#include "dma-ext.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOL 0.0000001
#define NTRIALS 3
#define SIZE_STEP 500

void saxpy(float a, float *x, float *y, int n, int prefetch)
{
	int i;

	if (prefetch) {
		dma_set_cr(SRC_STRIDE, 0);
		dma_set_cr(DST_STRIDE, 0);
		dma_set_cr(SEGMENT_SIZE, n * sizeof(float));
		dma_set_cr(NSEGMENTS, 1);

		dma_read_prefetch(x);
		dma_write_prefetch(y);
	}

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

unsigned long time_saxpy(int n, int prefetch)
{
	unsigned long starttime, endtime, totaltime = 0;
	float y[DATA_SIZE];
	int trial;

	for (trial = 0; trial < NTRIALS; trial++) {
		memcpy(y, input_data_Y, n * sizeof(float));

		starttime = rdtime();
		saxpy(input_data_a, input_data_X, y, n, prefetch);
		endtime = rdtime();

		totaltime += (endtime - starttime);
	}

	return totaltime / NTRIALS;
}

int main(int argc, char *argv[])
{
	unsigned long pf_time, npf_time;
	int n;
	FILE *f = NULL;

	printf("starting saxpy benchmark\n");

	if (argc > 1) {
		printf("writing output to %s\n", argv[1]);
		f = fopen(argv[1], "w");
		if (f == NULL) {
			perror("fopen");
			exit(EXIT_FAILURE);
		}
	}


	for (n = SIZE_STEP; n <= DATA_SIZE; n += SIZE_STEP) {
		npf_time = time_saxpy(n, 0);
		pf_time = time_saxpy(n, 1);
		printf("n = %d, no prefetch time = %lu, prefetch time = %lu\n",
				n, npf_time, pf_time);
		if (f) fprintf(f, "%d,%lu,%lu\n", n, npf_time, pf_time);
	}

	if (f) fclose(f);

	return 0;
}
