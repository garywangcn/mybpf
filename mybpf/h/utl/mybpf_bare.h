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

int MYBPF_BARE_Convert2File(char *src_filename, char *dst_filename, MYBPF_SIMPLE_CONVERT_PARAM_S *p);
int MYBPF_RunBare(void *mem, int mem_len, void **tmp_helpers, MYBPF_PARAM_S *p);
int MYBPF_RunBareFile(char *file, void **tmp_helpers, char *params);

#ifdef __cplusplus
}
#endif
#endif 
