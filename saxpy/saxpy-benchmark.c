#include "util.h"
#include "dataset.h"
#include "dma-ext.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PREFETCH_LOOKAHEAD 2048
#define PREFETCH_SIZE 4096
#define TOL 0.0000001
#define NTRIALS 3
#define SIZE_STEP 500

static inline int prefetch_needed(int i, int n)
{
	return i % PREFETCH_SIZE == 0 && (i + PREFETCH_LOOKAHEAD) < n;
}

void saxpy(float a, float *x, float *y, int n, int prefetch)
{
	int i;

	dma_set_cr(SRC_STRIDE, 0);
	dma_set_cr(DST_STRIDE, 0);
	//dma_set_cr(SEGMENT_SIZE, n * sizeof(float));
	dma_set_cr(SEGMENT_SIZE, PREFETCH_SIZE * sizeof(float));
	dma_set_cr(NSEGMENTS, 1);

	dma_write_prefetch(y);
	dma_read_prefetch(x);

	for (i = 0; i < n; i++) {
		if (prefetch && prefetch_needed(i, n)) {
			dma_write_prefetch(&y[i + PREFETCH_LOOKAHEAD]);
			dma_read_prefetch(&x[i + PREFETCH_LOOKAHEAD]);
		}
		y[i] += a * x[i];
	}
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
	float y[n];
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

/* This makes sure all the runs start as if the data had already been passed
 * through once. */
void warmup_cache(int n)
{
	float y[n];

	dma_set_cr(SRC_STRIDE, 0);
	dma_set_cr(DST_STRIDE, 0);
	dma_set_cr(SEGMENT_SIZE, n * sizeof(float));
	dma_set_cr(NSEGMENTS, 1);

	dma_write_prefetch(y);
	dma_read_prefetch(input_data_X);
	asm volatile ("fence");
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

	time_saxpy(DATA_SIZE, 0);

	for (n = SIZE_STEP; n <= DATA_SIZE; n += SIZE_STEP) {
		warmup_cache(n);
		npf_time = time_saxpy(n, 0);
		pf_time = time_saxpy(n, 1);
		printf("n = %d, no prefetch time = %lu, prefetch time = %lu\n",
				n, npf_time, pf_time);
		if (f) fprintf(f, "%d,%lu,%lu\n", n, npf_time, pf_time);
	}

	if (f) fclose(f);

	return 0;
}
