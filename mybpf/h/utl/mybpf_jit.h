/*********************************************************
*   Copyright (C) LiXingang
*   Description: 
*
********************************************************/
#ifndef _MYBPF_JIT_H
#define _MYBPF_JIT_H

#include "mybpf_jit_def.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define MYBPF_JIT_EXCEPTION_FUNC_ID 0

typedef void * (*PF_MYBPF_JIT_GET_HELPER_BY_ID)(unsigned int id);

enum {
    MYBPF_EXCEPTION_CODE_DIV_0 = 0,
};

typedef struct {
    MYBPF_INSN_S *insts;
    UINT num_insts;
    int tail_call_func; 
    PF_MYBPF_JIT_GET_HELPER_BY_ID get_helper_by_id;
}MYBPF_JIT_VM_S;

typedef struct {
    void *insts;
    int insts_len; 
    int progs_count;
    ELF_PROG_INFO_S *progs;
}MYBPF_JIT_INSN_S;

enum {
    
    MYBPF_JIT_HELPER_MODE_ID = 0,

    
    MYBPF_JIT_HELPER_MODE_RAW,

    
    MYBPF_JIT_HELPER_MODE_AGENT,

    
    MYBPF_JIT_HELPER_MODE_ARRAY, 

    MYBPF_JIT_HELPER_MODE_MAX, 
};

enum {
    MYBPF_TRANS_MODE_JIT = 0,
    MYBPF_TRANS_MODE_AOT
};

typedef struct {
    UINT jit_arch: 8;
    UINT helper_mode: 4; 
    UINT translate_mode_aot: 1;  
    UINT aot_map_index_to_ptr: 1; 
    UINT mmap_exe: 1; 
    UINT param_6th: 1; 

    int tail_call_func; 
    PF_MYBPF_JIT_GET_HELPER_BY_ID get_helper_by_id;
}MYBPF_JIT_CFG_S;

int MYBPF_JIT_GetJitTypeByName(char *jit_arch_name);
int MYBPF_JIT_LocalArch(void);
char * MYBPF_JIT_GetArchName(int arch_type);

int MYBPF_Jit(MYBPF_JIT_INSN_S *jit_insn, MYBPF_JIT_CFG_S *cfg);

#ifdef __cplusplus
}
#endif
#endif 
