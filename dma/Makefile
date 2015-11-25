CC=riscv64-unknown-linux-gnu-gcc
CFLAGS=-Wall -O2

TESTS = simple-test matrix-test

all: $(TESTS)

%: %.c dma-ext.h
	$(CC) $(CFLAGS) $< -static -o $@

clean:
	rm -rf $(TESTS)
