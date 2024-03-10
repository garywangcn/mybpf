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
int MYBPF_BARE_RunBare(void *mem, int mem_len, int argc, char **argv);
int MYBPF_BARE_RunFile(char *file, char *params);

#ifdef __cplusplus
}
#endif
#endif 
