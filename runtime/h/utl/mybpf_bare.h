/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0
* Description:
******************************************************************************/
#ifndef _MYBPF_BARE_H
#define _MYBPF_BARE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    U64 p[5];
}MYBPF_PARAM_S;

int MYBPF_RunBare(void *mem, int mem_len, void **tmp_helpers, MYBPF_PARAM_S *p);

#ifdef __cplusplus
}
#endif
#endif //MYBPF_BARE_H_
