#include "vls-segments.h"

int main(int argc, char **argv)
{
  u64 nsegs = getnvlssegs();
  if (nsegs != 1)
    return 0x1000 | nsegs;
  void *testptr = (void *) 0xF000000;
  setvlspbase(nsegs-1,testptr);
  void *readback = getvlspbase(nsegs-1);
  if (readback != testptr)
    return 0x2000;
  u64 testsize = WAY_SIZE;
  setvlssize(nsegs-1,testsize);
  u64 size = getvlssize(nsegs-1);
  if (size != testsize)
    return 0x4000;
  volatile u64 *vlsbuf = (volatile u64 *) testptr;
  u64 testval = 23;
  vlsbuf[0] = testval;
  u64 data = vlsbuf[0];
  if (data != testval)
    return 0x8000;
  return 0;
}
