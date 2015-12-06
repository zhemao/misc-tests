PK_TESTS=saxpy
HEADERS=dataset.h ../include/util.h

include ../Makefrag

dataset.h: gendata.py
	python gendata.py 1024 16384 > $@
