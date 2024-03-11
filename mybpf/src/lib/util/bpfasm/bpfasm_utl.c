/*********************************************************
*   Copyright (C) LiXingang
*   Description: 
*
********************************************************/
#include "bs.h"
#include "utl/bpfasm_utl.h"
#include "utl/mybpf_vm.h"

static inline BPFASM_FUNC_S * _bpfasm_find_by_func_name(BPFASM_S *ctrl, const char *func_name)
{
    BPFASM_FUNC_S *func = ctrl->funcs;

    while (func->func_name) {
        if (strcmp(func->func_name, func_name) == 0) {
            return func;
        }
        func ++;
    }

    return NULL;
}

int BPFASM_Run(BPFASM_S *ctrl, const char *func_name, OUT UINT64 *bpf_ret, MYBPF_PARAM_S *p)
{
    BPFASM_FUNC_S *f = _bpfasm_find_by_func_name(ctrl, func_name);
    void *code;

    if (! f) {
        RETURN(BS_NO_SUCH);
    }

    code = (MYBPF_INSN_S *)ctrl->begin_addr + f->insn_offset;

    return MYBPF_DefultRunCode(ctrl->begin_addr, ctrl->end_addr, code, bpf_ret, NULL, p);
}

