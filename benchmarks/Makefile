PK_TESTS=saxpy-benchmark
HEADERS=util.h dataset.h

include ../Makefrag

dataset.h: gendata.py
	python gendata.py 1024 16384 > $@
