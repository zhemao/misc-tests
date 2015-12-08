#include "util.h"
#include "dataset.h"
#include "dma-ext.h"
#include "test-settings.h"

#include <stdlib.h>

#define TOL 0.0000001
#define PREFETCH_LOOKAHEAD 128
#define PREFETCH_SIZE 4096

static inline int prefetch_needed(int i, int n)
{
	return i % PREFETCH_SIZE == 0 && (i + PREFETCH_LOOKAHEAD) < n;
}

void saxpy(float a, float *x, float *y, int n)
{
	int i;

#ifdef PREFETCH
	dma_set_cr(SRC_STRIDE, 0);
	dma_set_cr(DST_STRIDE, 0);
	dma_set_cr(SEGMENT_SIZE, PREFETCH_SIZE * sizeof(float));
	dma_set_cr(NSEGMENTS, 1);
#endif

	for (i = 0; i < n; i++) {
#ifdef PREFETCH
		if (prefetch_needed(i, n)) {
			dma_write_prefetch(&y[i + PREFETCH_LOOKAHEAD]);
			dma_read_prefetch(&x[i + PREFETCH_LOOKAHEAD]);
		}
#endif
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
	saxpy(input_data_a, input_data_X, input_data_Y, TEST_SIZE);

#ifdef VERIFY
	if (check_result(input_data_Y, verify_data, TEST_SIZE))
		return -1;
#endif

	return 0;
}
