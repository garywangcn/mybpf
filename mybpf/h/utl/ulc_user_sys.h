/*********************************************************
*   Copyright (C) LiXingang
*   Description: 给ULC用户使用的头文件
*
********************************************************/
#ifndef _ULC_USER_SYS_H
#define _ULC_USER_SYS_H

#include "ulc_user.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef IN_ULC_USER

#define malloc(a) ulc_sys_malloc(a)
#define calloc(a,b) ulc_sys_calloc(a,b)
#define free(a) ulc_sys_free(a)
#define strncmp(a,b,c) ulc_sys_strncmp(a,b,c)
#define strcmp(a,b) ulc_sys_strcmp(a,b)
#define strlen(a) ulc_sys_strlen(a)
#define strnlen(a,b) ulc_sys_strnlen(a,b)
#undef strlcpy
#define strlcpy(a,b,c) ulc_sys_strlcpy(a,b,c)
#define memcpy(a,b,c) ulc_sys_memcpy(a,b,c)
#define MMAP_Map(a,b,c) ulc_mmap_map(a,b,c)
#define MMAP_Unmap(a,b) ulc_mmap_unmap(a,b)
#define MMAP_MakeExe(a,b) ulc_mmap_make_exe(a,b)

#ifdef IN_ULC_IGN_GLOBAL 
#define ErrCode_Set(a,b,c,d,e) ulc_err_code_set(a,NULL,NULL,NULL,e)
#else
#define ErrCode_Set(a,b,c,d,e) ulc_err_code_set(a,b,c,d,e)
#endif

#undef assert
#define assert(x) 

#define flush(x) 

#undef RETURNI
#define RETURNI(_x, _fmt, ...)  do { \
    char _info[] = (_fmt); \
    ErrCode_Set(_x, NULL, __FILE__, __FUNCTION__, __LINE__); \
    ulc_err_info_set(_info, ##__VA_ARGS__); \
    return(_x); \
} while(0)

#undef BS_WARNNING
#define BS_WARNNING(X) BPF_Print X

#undef MEM_ZMalloc
#define MEM_ZMalloc(x) ({void *p = ulc_sys_malloc(x); if (p) {ulc_sys_memset(p, 0, (x));} p;})

#undef MEM_Malloc
#define MEM_Malloc(x) ulc_sys_malloc(x)

#undef MEM_Free
#define MEM_Free(x) ulc_sys_free(x)

static void * (*ulc_sys_malloc)(int size) = (void *) 1000000;
static void * (*ulc_sys_calloc)(int nitems, int size) = (void *) 1000001;
static void (*ulc_sys_free)(void *m) = (void *) 1000002;
static void (*ulc_sys_memcpy)(void *d, void *s, int len) = (void*)1000003;
static void (*ulc_sys_memset)(void *d, int c, int len) = (void*)1000004;
static void (*ulc_err_code_set)(int err_code, char *info, const char *file_name, const char *func_name, int line) = (void*)1000005;
static void (*ulc_err_info_set)(const char *fmt, ...) = (void*)1000006;
static void (*ulc_call_back)(void *func, void *p1, void *p2, void *p3, void *p4)= (void*)1000007;
static int (*ulc_sys_strncmp)(void *a, void *b, int len) = (void*)1000008;
static int (*ulc_sys_strlen)(void *a) = (void*)1000009;
static int (*ulc_sys_strnlen)(void *a, int max_len) = (void*)1000010;
static int (*ulc_sys_strcmp)(void *a, void *b) = (void*)1000011;
static int (*ulc_sys_strlcpy)(void *dst, void *src, int size) = (void*)1000012;
static void * (*ulc_mmap_map)(void *buf, int buf_size, int head_size) = (void*)1000013;
static void (*ulc_mmap_unmap)(void *buf, int size) = (void*)1000014;
static int (*ulc_mmap_make_exe)(void *buf, int size) = (void*)1000015;

#endif

#ifdef __cplusplus
}
#endif
#endif
