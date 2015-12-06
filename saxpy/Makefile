PK_TESTS=saxpy
HEADERS=dataset.h ../include/util.h

include ../Makefrag

dataset.h: saxpy_gendata.py
	python saxpy_gendata.py > $@
