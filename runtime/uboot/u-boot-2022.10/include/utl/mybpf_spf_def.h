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
    SPF_CMD_INIT = 0, /* 初始化 */
    SPF_CMD_FIN,      /* 去初始化 */
    SPF_CMD_LOAD,     /* 加载spf file */
    SPF_CMD_UNLOAD,   /* 卸载instance */
    SPF_CMD_UNLOAD_ALL,   /* 卸载instances */
    SPF_CMD_RUN,      /* 运行SPF */
    SPF_CMD_SHOW,     /* 显示instance */
};

#ifdef __cplusplus
}
#endif
#endif //MYBPF_SPF_DEF_H_
