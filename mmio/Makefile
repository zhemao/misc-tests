CFLAGS=-Wall -O1

CC=riscv64-unknown-linux-gnu-gcc
OBJDUMP=riscv64-unknown-linux-gnu-objdump

TESTS=csr-test atomic-test
HEX=$(addsuffix .hex,$(TESTS))
DUMP=$(addsuffix .dump,$(TESTS))

default: $(HEX) $(DUMP) $(LNX_EXE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

%.elf: %.o init.o ../link.ld
	$(CC) init.o $< -static -nostdlib -T../link.ld -o $@

%.hex: %.elf
	elf2hex 16 32768 $< > $@

%.dump: %.elf
	$(OBJDUMP) -D $< > $@
