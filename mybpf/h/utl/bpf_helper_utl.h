/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0  Date: 2017-10-3
* Description: 
******************************************************************************/
#ifndef _BPF_HELPER_UTL_H
#define _BPF_HELPER_UTL_H
#ifdef __cplusplus
extern "C"
{
#endif

#define BPF_BASE_HELPER_COUNT 1024
#define BPF_BASE_HELPER_END (BPF_BASE_HELPER_COUNT)

#define BPF_SYS_HELPER_START 1000000
#define BPF_SYS_HELPER_COUNT 256
#define BPF_SYS_HELPER_END (BPF_SYS_HELPER_START + BPF_SYS_HELPER_COUNT)

#define BPF_USER_HELPER_START 2000000
#define BPF_USER_HELPER_COUNT 256
#define BPF_USER_HELPER_END (BPF_USER_HELPER_START + BPF_USER_HELPER_COUNT)

typedef UINT64 (*PF_BPF_HELPER_FUNC)(UINT64 p1, UINT64 p2, UINT64 p3, UINT64 p4, UINT64 p5);

void * BpfHelper_GetFunc(unsigned int id);
int BpfHelper_RegUserFunc(UINT id, void *func);
const void ** BpfHelper_BaseHelper(void);
const void ** BpfHelper_SysHelper(void);
const void ** BpfHelper_UserHelper(void);

#ifdef __cplusplus
}
#endif
#endif 
