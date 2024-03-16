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
    U32 size; /* 文件大小,包含此头部 */

    U8 ver;
    U8 jit_arch;
    U16 bss_size; /*MYBPF_BARE_BSS_BLOCK_SIZE 字节元组个数,所以最多MYBPF_BARE_BSS_BLOCK_SIZE* 64k*/
    U16 app_ver;  /* APP版本号 */
    U16 depends_count; /* depend helper count */

    U32 utc_sec;      /* 生成时间, 自utc以来的秒数 */
    U8 reserved2[12];
}MYBPF_BARE_HDR_S;

typedef struct {
    int prog_len;
    void *prog;
    void **bss;
}MYBPF_BARE_S;

#ifdef __cplusplus
}
#endif
#endif //MYBPF_BARE_DEF_H_
