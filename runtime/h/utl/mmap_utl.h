/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0
* Description:
******************************************************************************/
#ifndef _MMAP_UTL_H_
#define _MMAP_UTL_H_

#ifdef __cplusplus
extern "C" {
#endif

void * MMAP_Map(void *buf, int buf_size, int map_size);
void MMAP_Unmap(void *buf, int total_size);
int MMAP_MakeExe(void *buf, int size);

#ifdef __cplusplus
}
#endif
#endif 
