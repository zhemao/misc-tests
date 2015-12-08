#ifndef __VLS_TRANS_H__
#define __VLS_TRANS_H__

#define TIME      0xC01

#define VLSVBASE  0xCF0
#define VLSSIZE   0xCF1

#define VLSVBASEW 0x9F0
#define VLSPBASE  0x5F0
#define VLSSIZEW  0x9F1

static inline unsigned long get_time(void)
{
  unsigned long vbase;
  asm volatile ("csrr %0, %1"
                : "=r"(vbase)
                : "i"(TIME));
  return vbase;
}

static inline void *vls_get_vbase(void)
{
  void *vbase;
  asm volatile ("csrr %0, %1"
                : "=r"(vbase)
                : "i"(VLSVBASE));
  return vbase;
}

static inline void vls_set_vbase(void *vbase)
{
  asm volatile ("csrw %0, %1"
                :
                : "i"(VLSVBASEW), "r"(vbase));
}

#endif
