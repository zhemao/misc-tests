output_dir=../output

LDFLAGS=-static -nostdlib -Tlink.ld
CFLAGS=-Wall -O1

CC=riscv64-unknown-linux-gnu-gcc
OBJDUMP=riscv64-unknown-linux-gnu-objdump

BM_TESTS=smallmem-test csr-test decerr-test atomic-test
BASENAMES=$(addprefix $(output_dir)/,$(BM_TESTS))
HEX=$(addsuffix .hex,$(BASENAMES))
DUMP=$(addsuffix .dump,$(BASENAMES))

LNX_TESTS=lnx-smallmem-test pk-memtest
LNX_EXE=$(addprefix $(output_dir)/,$(LNX_TESTS))

default: $(HEX) $(DUMP) $(LNX_EXE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

$(output_dir)/%: %.o
	$(CC) $< -static -o $@

$(output_dir)/%.elf: %.o init.o link.ld
	$(CC) init.o $< $(LDFLAGS) -o $@

$(output_dir)/%.hex: $(output_dir)/%.elf
	elf2hex 16 32768 $< > $@

$(output_dir)/%.dump: $(output_dir)/%.elf
	$(OBJDUMP) -D $< > $@
