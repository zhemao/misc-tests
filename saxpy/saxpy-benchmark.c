#include "util.h"
#include "dataset.h"
#include "dma-ext.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOL 0.0000001

void saxpy(float a, float *x, float *y, int n, size_t pf_size)
{
	int i;

	dma_set_cr(SRC_STRIDE, 0);
	dma_set_cr(DST_STRIDE, 0);
	dma_set_cr(SEGMENT_SIZE, pf_size * sizeof(float));
	dma_set_cr(NSEGMENTS, 1);

	if (pf_size == n) {
		dma_read_prefetch(x);
		dma_write_prefetch(y);
		pf_size = 0;
	}

	for (i = 0; i < n; i++) {
		if (pf_size > 0 && i % pf_size == 0 && i + pf_size < n) {
			dma_read_prefetch(&x[i + pf_size]);
			dma_write_prefetch(&y[i + pf_size]);
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

unsigned long time_saxpy(int pf_size)
{
	unsigned long starttime, endtime;
	float y[DATA_SIZE];

	memcpy(y, input_data_Y, DATA_SIZE * sizeof(float));

	starttime = rdtime();
	saxpy(input_data_a, input_data_X, y, DATA_SIZE, pf_size);
	endtime = rdtime();

	if (check_result(y, verify_data, DATA_SIZE)) {
		fprintf(stderr, "results do not match expected\n");
		exit(EXIT_FAILURE);
	}

	return endtime - starttime;
}

#define BLOCK_SIZE 16

static inline int benchmark_done(int blocks)
{
	unsigned long pf_size = blocks * BLOCK_SIZE;
	unsigned long test_size = DATA_SIZE * sizeof(float);
	return pf_size > (test_size / 2);
}

int main(int argc, char *argv[])
{
	unsigned long bm_time, last_time;
	int blocks;

	printf("starting saxpy benchmark\n");

	bm_time = time_saxpy(0);
	printf("no prefetching: %lu ticks\n", bm_time);

	for (blocks = 1; !benchmark_done(blocks); blocks *= 2) {
		last_time = bm_time;
		bm_time = time_saxpy(BLOCK_SIZE * blocks);
		printf("prefetch %d blocks: %lu ticks\n", blocks, bm_time);
		// stop the test once we are no longer getting faster
		if (bm_time > last_time)
			break;
	}

	bm_time = time_saxpy(DATA_SIZE);
	printf("full prefetch: %lu ticks\n", bm_time);

	return 0;
}
