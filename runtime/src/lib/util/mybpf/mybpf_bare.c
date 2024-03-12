/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0
* Description:
******************************************************************************/
#include "bs.h"
#include "utl/bpf_helper_utl.h"
#include "utl/mybpf_jit_def.h"
#include "utl/mybpf_jit.h"
#include "utl/mybpf_bare.h"
#include "utl/mybpf_prog_def.h"
#include "utl/mmap_utl.h"

#define MYBPF_BARE_MAGIC 0x7781648d

typedef struct {
    U32 magic;
    U32 size; 
    U8 ver;
    U8 jit_arch;
    U8 reserved[6];
}MYBPF_BARE_HDR_S;

static int _runbpf_run_bare_aoted(void *data, int len, void **tmp_helpers, MYBPF_PARAM_S *p)
{
    MYBPF_AOT_PROG_CTX_S ctx = {0};
    int (*fn)(U64,U64,U64,U64,U64,void*);
    int ret;

    ctx.base_helpers = BpfHelper_BaseHelper();
    ctx.sys_helpers = BpfHelper_SysHelper();
    ctx.user_helpers = BpfHelper_UserHelper();
    ctx.tmp_helpers = (const void **)tmp_helpers;

    fn = MMAP_Map(data, len, 0);
    if (! fn) {
        RETURNI(BS_ERR, "Can't map prog");
    }

    MMAP_MakeExe(fn, len);

    ret = fn(p->p[0], p->p[1], p->p[2], p->p[3], p->p[4], &ctx);

    MMAP_Unmap(fn, len);

    return ret;
}

static int _mybpf_get_bare_size(void *mem, int mem_len)
{
    MYBPF_BARE_HDR_S *hdr = mem;

    if (mem_len <= sizeof(*hdr)) {
        
        RETURNI(BS_TOO_SMALL, "Too small");
    }

    if (hdr->magic != htonl(MYBPF_BARE_MAGIC)) {
        
        RETURNI(BS_NOT_MATCHED, "Magic not match");
    }

    int size = ntohl(hdr->size);
    if (size > mem_len) {
        
        RETURNI(BS_WRONG_FILE, "File length not valid");
    }

    return size;
}

int MYBPF_RunBare(void *mem, int mem_len, void **tmp_helpers, MYBPF_PARAM_S *p)
{
    int ret;
    int size;
    void *begin;
    MYBPF_BARE_HDR_S *hdr = mem;

    size = _mybpf_get_bare_size(mem, mem_len);
    if (size < 0) {
        return size;
    }

    begin = (char*)mem + sizeof(MYBPF_BARE_HDR_S);

    if (! hdr->jit_arch) {
        RETURNI(BS_NOT_SUPPORT, "Need aot");
    }

    if (hdr->jit_arch == MYBPF_JIT_LocalArch()) {
        ret = _runbpf_run_bare_aoted(begin, size - sizeof(MYBPF_BARE_HDR_S), tmp_helpers, p);
    } else {
        RETURNI(BS_NOT_SUPPORT, "Jit arch not matched");
    }

    return ret;
}

