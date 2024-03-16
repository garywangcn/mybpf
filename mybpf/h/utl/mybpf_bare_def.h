/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0
* Description:
******************************************************************************/
#ifndef _MYBPF_BARE_DEF_H_
#define _MYBPF_BARE_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MYBPF_BARE_MAGIC 0x7781648d
#define MYBPF_BARE_BSS_BLOCK_SIZE 16

typedef struct {
    U32 magic;
    U32 size; 

    U8 ver;
    U8 jit_arch;
    U16 bss_size; 
    U16 app_ver;  
    U8 reserved1[2];

    U32 utc_sec;      
    U8 reserved2[12];
}MYBPF_BARE_HDR_S;

typedef struct {
    void *prog;
    int prog_len;
    void **bss;
}MYBPF_BARE_S;

#ifdef __cplusplus
}
#endif
#endif 
