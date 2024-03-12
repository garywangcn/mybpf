/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0  Date: 2017-10-3
* Description: 
*
******************************************************************************/
#include "bs.h"
#include "utl/bpf_helper_utl.h"

long __bpfprobe_read(void *dst, U32 size, const void *unsafe_ptr)
{
    if ((! dst) || (! unsafe_ptr)) {
        return -1;
    }

    memcpy(dst, unsafe_ptr, size);

    return 0;
}

U64 __bpfktime_get_ns(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    return ((U64)ts.tv_sec * 1000000000 + (U64)ts.tv_nsec);
}

long __bpftrace_printk(const char *fmt, U32 fmt_size, void *p1, void *p2, void *p3)
{
    printf(fmt, p1, p2, p3);
    return 0;
}

U32 __bpfget_prandom_u32(void)
{
    return rand();
}

long __bpfstrtol(const char *buf, size_t buf_len, U64 flags, long *res)
{
    char *end;
    *res = strtol(buf, &end, flags);
    return end - buf;
}

long __bpfstrtoul(const char *buf, size_t buf_len, U64 flags, unsigned long *res)
{
    char *end;
    *res = strtoul(buf, &end, flags);
    return end - buf;
}

void * ulc_sys_malloc(int size)
{
    return malloc(size);
}

void * ulc_sys_calloc(int nitems, int size)
{
    return calloc(nitems, size);
}

void ulc_sys_free(void *m)
{
    free(m);
}

int ulc_sys_strcmp(void *a, void *b)
{
    return strcmp(a, b);
}

int ulc_sys_strncmp(void *a, void *b, int len)
{
    return strncmp(a, b, len);
}

int ulc_sys_strlen(void *a)
{
    return strlen(a);
}

int ulc_sys_strlcpy(char *dst, char *src, int size)
{
    unsigned long n;
    char *p;

    for (p = dst, n = 0; n + 1 < size && *src!= '\0';  ++p, ++src, ++n) {
        *p = *src;
    }
    *p = '\0';
    if(*src == '\0') {
        return n;
    } else {
        return n + strlen(src);
    }
}

int ulc_sys_strnlen(void *a, int max_len)
{
    return strnlen(a, max_len);
}

void ulc_sys_memcpy(void *d, void *s, int len)
{
    memcpy(d, s, len);
}

void ulc_sys_memset(void *d, int c, int len)
{
    memset(d, c, len);
}

/* base helper. 和linux内置定义helper一一对应,请不要注册和linux不一致的helper */
static const void * g_bpf_base_helpers[BPF_BASE_HELPER_COUNT] = {
    [4] = __bpfprobe_read,
    [5] = __bpfktime_get_ns,
    [6] = __bpftrace_printk,
    [7] = __bpfget_prandom_u32,
    [105] = __bpfstrtol,
    [106] = __bpfstrtoul,
};
/* sys helper. linux系统定义之外的统一定义, 请不要随意定义 */
static const void * g_bpf_sys_helpers[BPF_SYS_HELPER_COUNT] = {
    [0] = ulc_sys_malloc, /* 1000000 */
    [1] = ulc_sys_calloc,
    [2] = ulc_sys_free,
    [3] = ulc_sys_memcpy,
    [4] = ulc_sys_memset,
    [8] = ulc_sys_strncmp,
    [9] = ulc_sys_strlen,
    [10] = ulc_sys_strnlen,
    [11] = ulc_sys_strcmp,
    [12] = ulc_sys_strlcpy,
};
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

