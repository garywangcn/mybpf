/*********************************************************
*   Copyright (C) LiXingang
*   Description: 
*
********************************************************/
#ifndef _MYBPF_JIT_DEF_H
#define _MYBPF_JIT_DEF_H
#ifdef __cplusplus
extern "C"
{
#endif

enum {
    MYBPF_JIT_ARCH_NONE = 0,
    MYBPF_JIT_ARCH_ARM64,
    MYBPF_JIT_ARCH_X86_64,

    MYBPF_JIT_ARCH_MAX
};

#ifdef __cplusplus
}
#endif
#endif 
