#include "util.h"
#include "dataset.h"
#include "dma-ext.h"

#include <stdlib.h>

#define TOL 0.0000001
#define PREFETCH_SIZE 0
#define TEST_SIZE 128

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

int main(int argc, char *argv[])
{
	saxpy(input_data_a, input_data_X, input_data_Y,
			TEST_SIZE, PREFETCH_SIZE);

	if (check_result(input_data_Y, verify_data, TEST_SIZE))
		return -1;

	return 0;
}
