PK_TESTS=saxpy-benchmark
BM_TESTS=saxpy-test
HEADERS=dataset.h ../include/util.h ../include/dma-ext.h

include ../Makefrag

dataset.h: saxpy_gendata.py
	python saxpy_gendata.py > $@
