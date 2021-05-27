#pragma once
#include "hplatform.h"
#include <endian.h>

#define PI8(p)          *(int8_t*)(p)
#define PI16(p)         *(int16_t*)(p)
#define PI32(p)         *(int32_t*)(p)
#define PI64(p)         *(int64_t*)(p)

#define PU8(p)          *(uint8_t*)(p)
#define PU16(p)         *(uint16_t*)(p)
#define PU32(p)         *(uint32_t*)(p)
#define PU64(p)         *(uint64_t*)(p)

#define PF32(p)         *(float*)(p)
#define PF64(p)         *(double*)(p)

#define GET_BE16(p)     be16toh(PU16(p))
#define GET_BE32(p)     be32toh(PU32(p))
#define GET_BE64(p)     be64toh(PU64(p))

#define GET_LE16(p)     le16toh(PU16(p))
#define GET_LE32(p)     le32toh(PU32(p))
#define GET_LE64(p)     le64toh(PU64(p))

#define PUT_BE16(p, v)  PU16(p) = htobe16(v)
#define PUT_BE32(p, v)  PU32(p) = htobe32(v)
#define PUT_BE64(p, v)  PU64(p) = htobe64(v)

#define PUT_LE16(p, v)  PU16(p) = htole16(v)
#define PUT_LE32(p, v)  PU32(p) = htole32(v)
#define PUT_LE64(p, v)  PU64(p) = htole64(v)

//note: uint8_t* p = (uint8_t*)buf;
#define POP_BE8(p, v)   v = *p; ++p
#define POP_BE16(p, v)  v = be16toh(PU16(p)); p += 2
#define POP_BE32(p, v)  v = be32toh(PU32(p)); p += 4
#define POP_BE64(p, v)  v = be64toh(PU64(p)); p += 8

#define POP_LE8(p, v)   v= *p; ++p
#define POP_LE16(p, v)  v = le16toh(PU16(p)); p += 2
#define POP_LE32(p, v)  v = le32toh(PU32(p)); p += 4
#define POP_LE64(p, v)  v = le64toh(PU64(p)); p += 8

#define PUSH_BE8(p, v)  *p = v; ++p
#define PUSH_BE16(p, v) PU16(p) = htobe16(v); p += 2
#define PUSH_BE32(p, v) PU32(p) = htobe32(v); p += 4
#define PUSH_BE64(p, v) PU64(p) = htobe64(v); p += 8

#define PUSH_LE8(p, v)  *p = v; ++p
#define PUSH_LE16(p, v) PU16(p) = htole16(v); p += 2
#define PUSH_LE32(p, v) PU32(p) = htole32(v); p += 4
#define PUSH_LE64(p, v) PU64(p) = htole64(v); p += 8

static inline int detect_endian()
{
    union
    {
        char c;
        short s;
    }u;
    u.s = 0x1122;
    if(u.c == 0x11)
    {
        return BIG_ENDIAN;
    }
    return LITTLE_ENDIAN;
}
