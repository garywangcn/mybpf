/*================================================================
*   Created by LiXingang, Copyright LiXingang
*   Description: 
*
================================================================*/
#ifndef _MYBPF_PROG_H
#define _MYBPF_PROG_H

#include "utl/mybpf_utl.h"
#include "utl/mybpf_runtime.h"
#include "utl/mybpf_vm.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define MYBPF_PROG_MAX_MAPS	32

typedef struct {
    RCU_NODE_S rcu_node;
    char sec_name[128];
    char prog_name[64];
    void *loader_node;
    UINT attached; 
    int insn_len; 
    void *insn; 
}MYBPF_PROG_NODE_S;

typedef struct xdp_buff {
	void *data;
	void *data_end;
	void *data_meta;
	
	UINT ingress_ifindex; 
	UINT rx_queue_index; 
}MYBPF_XDP_BUFF_S;

void MYBPF_PROG_Free(MYBPF_RUNTIME_S *runtime, MYBPF_PROG_NODE_S *prog);
void MYBPF_PROG_ShowProg(MYBPF_RUNTIME_S *runtime, PF_PRINT_FUNC print_func);
MYBPF_PROG_NODE_S * MYBPF_PROG_GetByFuncName(MYBPF_RUNTIME_S *runtime, char *instance, char *func_name);
MYBPF_PROG_NODE_S * MYBPF_PROG_GetBySecName(MYBPF_RUNTIME_S *runtime, char *instance, char *sec_name);
MYBPF_PROG_NODE_S * MYBPF_PROG_GetNext(MYBPF_RUNTIME_S *runtime, char *instance, char *sec_name,
        MYBPF_PROG_NODE_S *current);
int MYBPF_PROG_Run(MYBPF_PROG_NODE_S *prog, OUT UINT64 *bpf_ret, MYBPF_PARAM_S *p);

int MYBPF_PROG_FixupExtCalls(void *insts, int len);

#ifdef __cplusplus
}
#endif
#endif 
