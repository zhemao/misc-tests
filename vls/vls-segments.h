#define VLS_CONF_BASE 0x40200000
#define WAY_SIZE 0x40000 // 8 way, 2048kB -> 18 untag bits

typedef unsigned long long u64;

static inline u64 getnvlssegs(void)
{
  volatile u64 *vls_conf = (volatile u64 *) VLS_CONF_BASE;
  return *vls_conf;
}

static inline void *getvlspbase(u64 segnum)
{
  volatile u64 *vls_conf = (volatile u64 *) VLS_CONF_BASE;
  return (void *) vls_conf[2*(segnum+1)];
}

static inline void setvlspbase(u64 segnum, void *pbase)
{
  volatile u64 *vls_conf = (volatile u64 *) VLS_CONF_BASE;
  vls_conf[2*(segnum+1)] = (u64) pbase;
}

static inline u64 getvlssize(u64 segnum)
{
  volatile u64 *vls_conf = (volatile u64 *) VLS_CONF_BASE;
  return vls_conf[2*(segnum+1)+1];
}

static inline void setvlssize(u64 segnum, u64 size)
{
  volatile u64 *vls_conf = (volatile u64 *) VLS_CONF_BASE;
  vls_conf[2*(segnum+1)+1] = size;
}
