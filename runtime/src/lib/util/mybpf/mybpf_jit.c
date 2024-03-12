/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0
* Description:
******************************************************************************/
#include "utl/mybpf_jit_def.h"


int MYBPF_JIT_LocalArch(void)
{
#ifdef __aarch64__
    return MYBPF_JIT_ARCH_ARM64;
#endif

#ifdef __x86_64__
    return MYBPF_JIT_ARCH_X86_64;
#endif
}

