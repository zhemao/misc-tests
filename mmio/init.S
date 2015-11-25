.text
.align 4
.global _start

_start:
  // don't proceed if hartid isn't 0
  csrr a0, mhartid
  bnez a0, extra_core
  // init stack pointer
  li sp, 0x20000000
  // call C code
  jal main
  // write return code to mtohost
  slli a0, a0, 1
  ori a0, a0, 1
_finish:
  csrw mtohost, a0
  j _finish
extra_core:
  j extra_core
