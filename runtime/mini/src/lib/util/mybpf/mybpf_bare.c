/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0
* Description:
******************************************************************************/
#include <sys/mman.h>
#include "bs.h"
#include "utl/bpf_helper_utl.h"
#include "utl/arch_utl.h"
#include "utl/mybpf_jit_def.h"
#include "utl/mybpf_bare.h"
#include "utl/mybpf_prog_def.h"
#include "utl/mmap_utl.h"

static int _runbpf_run_bare(void *data, int len, void **tmp_helpers, MYBPF_PARAM_S *p)
{
    MYBPF_AOT_PROG_CTX_S ctx = {0};
    int (*fn)(U64,U64,U64,U64,U64,void*);

    ctx.base_helpers = BpfHelper_BaseHelper();
    ctx.sys_helpers = BpfHelper_SysHelper();
    ctx.user_helpers = BpfHelper_UserHelper();
    ctx.tmp_helpers = (const void **)tmp_helpers;

    fn = mmap(0, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (! fn) {
        RETURNI(BS_ERR, "Can't map prog");
    }

    memcpy(fn, data, len);
    mprotect(fn, len, PROT_READ | PROT_EXEC);

    int ret = fn(p->p[0], p->p[1], p->p[2], p->p[3], p->p[4], &ctx);

    munmap(fn, len);

    return ret;
}

static int _mybpf_get_bare_size(void *mem)
{
    MYBPF_BARE_HDR_S *hdr = mem;

    if (hdr->magic != htonl(MYBPF_BARE_MAGIC)) {
        /* 魔数不对 */
        RETURNI(BS_NOT_MATCHED, "Magic not match");
    }

    if ((! hdr->jit_arch) || (hdr->jit_arch != ARCH_LocalArch())) {
        RETURNI(BS_NOT_SUPPORT, "Jit arch not matched");
    }

    return ntohl(hdr->size);
}

int MYBPF_RunBare(void *mem, void **tmp_helpers, MYBPF_PARAM_S *p)
{
    MYBPF_BARE_HDR_S *hdr = mem;

    int size = _mybpf_get_bare_size(mem);
    if (size < 0) {
        return size;
    }

    int head_size = sizeof(*hdr) + sizeof(int) * ntohs(hdr->depends_count);

    return _runbpf_run_bare((char*)mem + head_size, size - head_size, tmp_helpers, p);
}

