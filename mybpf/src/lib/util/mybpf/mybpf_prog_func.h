/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0
* Description:
******************************************************************************/
#ifndef _MYBPF_PROG_FUNC_H_
#define _MYBPF_PROG_FUNC_H_

#ifdef __cplusplus
extern "C" {
#endif

MYBPF_PROG_NODE_S * _MYBPF_PROG_GetFirst(MYBPF_RUNTIME_S *runtime,
        MYBPF_LOADER_NODE_S *loader, char *sec_name);

MYBPF_PROG_NODE_S * _MYBPF_PROG_GetNext(MYBPF_RUNTIME_S *runtime,
        MYBPF_LOADER_NODE_S *loader, char *sec_name, MYBPF_PROG_NODE_S *current);

#ifdef __cplusplus
}
#endif
#endif 
