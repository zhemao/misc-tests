#include "vls-segments.h"

#define USE_VLS 2

#define NHISTS   32
#define NBINS    32
#define NVECS    64 // NVECS >= NBINS

int main(int argc, char **argv)
{
  u64 *hists = (u64 *) 0x2000000;
  u64 *data = (u64 *)  0x4000000;
  // element i goes in ith hist
  for (int i = 0; i < NHISTS; i++)
    for (int bin = 0; bin < NBINS; bin++)
      *(hists + i*NBINS + bin) = 0;
#ifdef USE_VLS
  asm volatile ("fence");
  setvlspbase(0,hists);
  setvlssize(0,NHISTS*NBINS*sizeof(u64));
  asm volatile ("fence");
#endif
  for (int j = 0; j < NVECS; j++)
    for (int i = 0; i < NHISTS; i++)
      *(data + j*NHISTS + i) = j % NBINS; // uniform
  for (int j = 0; j < NVECS; j++) {
    for (int i = 0; i < NHISTS; i++) {
      u64 value = *(data + j*NHISTS + i);
      (*(hists + i*NBINS + value))++;
    }
  }
  u64 pop = NVECS / NBINS;
  for (int i = 0; i < NHISTS; i++)
    for (int bin = 0; bin < NBINS; bin++)
      if (*(hists + i*NBINS + bin) != pop)
        return 0x8000 | *(hists + i*NBINS + bin);
  return 0x1000;
}
