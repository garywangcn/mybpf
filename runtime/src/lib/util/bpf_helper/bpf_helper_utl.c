/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0  Date: 2017-10-3
* Description: 
*
******************************************************************************/
#include "bs.h"
#include "utl/bpf_helper_utl.h"

long __bpftrace_printk(const char *fmt, U32 fmt_size, void *p1, void *p2, void *p3)
{
    printf(fmt, p1, p2, p3);
    return 0;
}

/* base helper. 和linux内置定义helper一一对应,请不要注册和linux不一致的helper */
static const void * g_bpf_base_helpers[BPF_BASE_HELPER_COUNT] = {
    [6] = __bpftrace_printk,
};
/* sys helper. linux系统定义之外的统一定义, 请不要随意定义 */
static const void * g_bpf_sys_helpers[BPF_SYS_HELPER_COUNT];
/* user helper. 没有任何预规定，用户可以定义 */
static const void * g_bpf_user_helpers[BPF_USER_HELPER_COUNT];

const void ** BpfHelper_BaseHelper(void)
{
    return g_bpf_base_helpers;
}

const void ** BpfHelper_SysHelper(void)
{
    return g_bpf_sys_helpers;
}

const void ** BpfHelper_UserHelper(void)
{
    return (const void **)g_bpf_user_helpers;
}

/* 根据id获取helper函数指针 */
const void * BpfHelper_GetFunc(U32 id)
{
    if (id < BPF_BASE_HELPER_END) {
        return (void*)g_bpf_base_helpers[id];
    } else if ((id >= BPF_SYS_HELPER_START) && (id < BPF_SYS_HELPER_END)) {
        return (void*)g_bpf_sys_helpers[id - BPF_SYS_HELPER_START];
    } else if ((id >= BPF_USER_HELPER_START) && (id < BPF_USER_HELPER_END)) {
        return (void*)g_bpf_user_helpers[id - BPF_USER_HELPER_START];
    }

    return NULL;
}

int BpfHelper_RegFunc(U32 id, void *func)
{
    if (id < BPF_BASE_HELPER_END) {
        g_bpf_base_helpers[id] = func;
    } else if ((id >= BPF_SYS_HELPER_START) && (id < BPF_SYS_HELPER_END)) {
        g_bpf_sys_helpers[id - BPF_SYS_HELPER_START] = func;
    } else if ((BPF_USER_HELPER_START <= id) && (id < BPF_USER_HELPER_END)) {
        g_bpf_user_helpers[id - BPF_USER_HELPER_START] = func;
    } else {
        return -1;
    }

    return 0;
}

