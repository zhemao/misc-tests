#include "util.h"
#include "dataset.h"
#include "dma-ext.h"
#include "test-settings.h"

#include <stdlib.h>

#define TOL 0.0000001

void saxpy(float a, float *x, float *y, int n)
{
	int i;

#ifdef PREFETCH
	dma_set_cr(SRC_STRIDE, 0);
	dma_set_cr(DST_STRIDE, 0);
	dma_set_cr(SEGMENT_SIZE, n * sizeof(float));
	dma_set_cr(NSEGMENTS, 1);

	dma_read_prefetch(x);
	dma_write_prefetch(y);
#endif

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
	saxpy(input_data_a, input_data_X, input_data_Y, TEST_SIZE);

#ifdef VERIFY
	if (check_result(input_data_Y, verify_data, TEST_SIZE))
		return -1;
#endif

	return 0;
}
