/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0
* Description:
******************************************************************************/
#ifndef _MYBPF_SPF_DEF_H_
#define _MYBPF_SPF_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

enum {
    SPF_CMD_INIT = 0, 
    SPF_CMD_FIN,      
    SPF_CMD_LOAD,     
    SPF_CMD_UNLOAD,   
    SPF_CMD_UNLOAD_ALL,   
    SPF_CMD_RUN,
    SPF_CMD_SHOW,     /* 显示instance */
};

#ifdef __cplusplus
}
#endif
#endif 
