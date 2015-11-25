CFLAGS=-Wall -O1

CC=riscv64-unknown-linux-gnu-gcc
OBJDUMP=riscv64-unknown-linux-gnu-objdump

TESTS=accum-test
HEX=$(addsuffix .hex,$(TESTS))
DUMP=$(addsuffix .dump,$(TESTS))

default: $(HEX) $(DUMP) $(LNX_EXE)

%.o: %.c accel.h
	$(CC) $(CFLAGS) -c $< -o $@

%.elf: %.o ../init.S ../link.ld
	$(CC) ../init.S $< -static -nostdlib -T../link.ld -o $@

%.hex: %.elf
	elf2hex 16 32768 $< > $@

%.dump: %.elf
	$(OBJDUMP) -D $< > $@

clean:
	rm -f *.o *.elf *.hex *.dump
