/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0
* Description:
******************************************************************************/
#ifndef _MYBPF_BARE_H
#define _MYBPF_BARE_H

#include "mybpf_utl.h"
#include "mybpf_bare_def.h"

#ifdef __cplusplus
extern "C" {
#endif


BOOL_T MYBPF_IsBareFile(char *filename);

int MYBPF_LoadBareFile(char *file, OUT MYBPF_BARE_S *bare);
int MYBPF_LoadBare(void *data, int len, OUT MYBPF_BARE_S *bare);
void MYBPF_UnloadBare(MYBPF_BARE_S *bare);

U64 MYBPF_RunBare(MYBPF_BARE_S *bare, const void **tmp_helpers, MYBPF_PARAM_S *p);
U64 MYBPF_RunBareFile(char *file, const void **tmp_helpers, MYBPF_PARAM_S *p);

#ifdef __cplusplus
}
#endif
#endif 
