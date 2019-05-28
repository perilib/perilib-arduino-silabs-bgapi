#include "SilabsBGAPIProtocolBT121.h"

namespace Perilib
{

const uint8_t SilabsBGAPIProtocolBT121::commandTable[] =
{
    /* system_reset (ID=0/0) */
        /* group_id */      0x00,
        /* method_id */     0x00,
        /* outarg_count */  0x01,
        /* inarg_count */   0x80,
        /* cmda[0] */       UINT8,
        
    /* system_hello (ID=0/1) */
        /* group_id */      0x00,
        /* method_id */     0x01,
        /* outarg_count */  0x00,
        /* inarg_count */   0x00,
        
    /* system_whitelist_append (ID=0/10) */
        /* group_id */      0x00,
        /* method_id */     0x0A,
        /* outarg_count */  0x02,
        /* inarg_count */   0x01,
        /* cmda[0] */       MACADDR,
        /* cmda[1] */       UINT8,
        /* rspa[0] */       UINT16,
};

const uint8_t SilabsBGAPIProtocolBT121::eventTable[] =
{
    /* system_boot (ID=0/0) */
        /* group_id */      0x00,
        /* method_id */     0x00,
        /* inarg_count */   0x07,
        /* evta[0] */       UINT16, /* uint16 major */
        /* evta[1] */       UINT16, /* uint16 minor */
        /* evta[2] */       UINT16, /* uint16 patch */
        /* evta[3] */       UINT16, /* uint16 build */
        /* evta[4] */       UINT16, /* uint16 ll_version */
        /* evta[5] */       UINT8,  /* uint8 protocol_version */
        /* evta[6] */       UINT8,  /* uint8 hw */
};

} // namespace Perilib
