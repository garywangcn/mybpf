/*********************************************************
*   Copyright (C) LiXingang
*   Description: 
*
********************************************************/
#ifndef _MYBPF_ELF_H
#define _MYBPF_ELF_H

#include "utl/elf_utl.h"
#include "utl/umap_utl.h"
#include "utl/mybpf_utl.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef int (*PF_MYBPF_ELF_WALK_MAP)(int map_index, UMAP_ELF_MAP_S *map, int len, char *map_name, void *ud);

ELF_SECTION_S * MYBPF_ELF_GetProg(ELF_S *elf, char *func_name, OUT ELF_SECTION_S *sec);
void MYBPF_ELF_GetGlobalDataUsed(ELF_S *elf, OUT ELF_GLOBAL_DATA_S *global_data);
int MYBPF_ELF_GetMapsSection(ELF_S *elf, OUT MYBPF_MAPS_SEC_S *map_sec);
int MYBPF_ELF_WalkMap(ELF_S *elf, PF_MYBPF_ELF_WALK_MAP walk_func, void *ud);

int MYBPF_ELF_WalkMapByFile(char *file, PF_MYBPF_ELF_WALK_MAP walk_func, void *ud);
int MYBPF_ELF_WalkProgByFile(char *file, PF_ELF_WALK_PROG walk_func, void *ud);

#ifdef __cplusplus
}
#endif
#endif 
