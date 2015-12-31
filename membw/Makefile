PK_TESTS=membw
HEADERS=dataset.h ../include/util.h

include ../Makefrag

dataset.h: membw_gendata.py
	python membw_gendata.py > $@
