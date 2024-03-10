/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0
* Description:
******************************************************************************/
#include "bs.h"
#include "types.h"
#include "utl/mybpf_prog.h"
#include "utl/mybpf_elf.h"
#include "utl/mybpf_simple.h"


static inline FILE_MEM_S * _mybpf_simple_open_spf_file(char *simple_file)
{
    FILE_MEM_S *m = FILE_Mem(simple_file);
    if (! m) {
        return NULL;
    }

    if (m->len < sizeof(MYBPF_SIMPLE_HDR_S)) {
        FILE_MemFree(m);
        return NULL;
    }

    MYBPF_SIMPLE_HDR_S *hdr = (void*)m->data;

    if ((hdr->ver != MYBPF_SIMPLE_VER) || (hdr->magic != htonl(MYBPF_SIMPLE_MAGIC))) {
        FILE_MemFree(m);
        return NULL;
    }

    return m;
}

FILE_MEM_S * MYBPF_SIMPLE_OpenSpf(char *file)
{
    return _mybpf_simple_open_spf_file(file);
}

void MYBPF_SIMPLE_Close(FILE_MEM_S *f)
{
    FILE_MemFree(f);
}

