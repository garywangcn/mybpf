/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0
* Description:
******************************************************************************/
#ifndef _ULC_USER_USER_H_
#define _ULC_USER_USER_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef IN_ULC_USER

#ifdef IN_ULC_IGN_GLOBAL 
#define ErrCode_Set(a,b,c,d,e) ulc_err_code_set(a,NULL,NULL,NULL,e)
#else
#define ErrCode_Set(a,b,c,d,e) ulc_err_code_set(a,b,c,d,e)
#endif

#undef RETURNI
#define RETURNI(_x, _fmt, ...)  do { \
    char _info[] = (_fmt); \
    ErrCode_Set(_x, NULL, __FILE__, __FUNCTION__, __LINE__); \
    ulc_err_info_set(_info, ##__VA_ARGS__); \
    return(_x); \
} while(0)


static void (*ulc_err_code_set)(int err_code, char *info, const char *file_name, const char *func_name, int line) = (void*)2000000;
static void (*ulc_err_info_set)(const char *fmt, ...) = (void*)2000001;
static void (*ulc_call_back)(void *func, void *p1, void *p2, void *p3, void *p4)= (void*)2000002;

#endif

#ifdef __cplusplus
}
#endif
#endif 
