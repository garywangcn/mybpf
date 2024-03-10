/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0
* Description:
******************************************************************************/
#ifndef _MYBPF_SIMPLE_FUNC_H_
#define _MYBPF_SIMPLE_FUNC_H_

#ifdef __cplusplus
extern "C" {
#endif

static inline MYBPF_SIMPLE_COMMON_HDR_S * mybpf_simple_get_next_sec(FILE_MEM_S *m, void *cur_hdr)
{
    MYBPF_SIMPLE_COMMON_HDR_S *common_hdr = cur_hdr;
    UCHAR *next;

    if (! cur_hdr) {
        
        MYBPF_SIMPLE_HDR_S *hdr = (void*)m->data;
        return (void*)(hdr + 1);
    }

    next = (void*)((UCHAR*)common_hdr + ntohl(common_hdr->sec_size));
    if (next >= (m->data + m->len)) {
        
        return NULL;
    }

    return (void*)next;
}


static inline void * mybpf_simple_get_next_type_sec(FILE_MEM_S *m, int type, void *cur_hdr)
{
    MYBPF_SIMPLE_COMMON_HDR_S *common_hdr = cur_hdr;

    while ((common_hdr = mybpf_simple_get_next_sec(m, common_hdr))) {
        if (common_hdr->sec_type == type) {
            return common_hdr;
        }
    }

    return NULL;
}


static inline void * mybpf_simple_get_type_sec(FILE_MEM_S *m, int type, int id)
{
    MYBPF_SIMPLE_COMMON_HDR_S *common_hdr = NULL;
    int this_id = 0;

    while ((common_hdr = mybpf_simple_get_next_type_sec(m, type, common_hdr))) {
        if (this_id == id) {
            return common_hdr;
        }
        this_id ++;
    }

    return NULL;
}

static int mybpf_simple_get_sec_data_size(void *hdr)
{
    MYBPF_SIMPLE_COMMON_HDR_S *sec = hdr;
    int size;

    if (! hdr) {
        return 0;
    }

    size = ntohl(sec->sec_size);
    size -= sizeof(*sec);
    size -= sec->name_size;

    return size;
}

static int mybpf_simple_get_map_def_size(MYBPF_SIMPLE_MAP_HDR_S *hdr)
{
    U32 map_size;

    if (hdr->map_count == 0) {
        return 0;
    }

    map_size = mybpf_simple_get_sec_data_size(hdr);

    return map_size / hdr->map_count;
}

static void * mybpf_simple_get_sec_data(void *hdr)
{
    MYBPF_SIMPLE_COMMON_HDR_S *sec = hdr;
    char *d;

    if (! hdr) {
        return NULL;
    }

    if (mybpf_simple_get_sec_data_size(sec) == 0) {
        return NULL;
    }

    d = (void*)(sec + 1);
    d += sec->name_size;

    return d;
}

static char * mybpf_simple_get_sec_name(void *hdr)
{
    MYBPF_SIMPLE_COMMON_HDR_S *sec = hdr;

    if (sec->name_size == 0) {
        return NULL;
    }
    
    return (void*)(sec + 1);
}

static inline int _mybpf_simple_get_prog_names(FILE_MEM_S *m, int id, OUT char **sec_name, OUT char **func_name)
{
    int i;
    char *fname;
    char *sname;
    int func_count;
    MYBPF_SIMPLE_PROG_OFF_S *off;

    MYBPF_SIMPLE_PROG_INFO_HDR_S *hdr = mybpf_simple_get_type_sec(m, MYBPF_SIMPLE_SEC_TYPE_PROG_INFO, 0);
    if (! hdr) {
        RETURN(BS_NOT_FOUND);
    }

    func_count = ntohs(hdr->func_count);
    if (id >= func_count) {
        RETURN(BS_OUT_OF_RANGE);
    }

    off = mybpf_simple_get_sec_data(hdr);

    sname = (void*)(off + func_count);
    fname = sname + strlen(sname) + 1;

    for (i=0; i<id; i++) {
        sname = fname + strlen(fname) + 1;
        fname = sname + strlen(sname) + 1;
    }

    if (sec_name) {
        *sec_name = sname;
    }

    if (func_name) {
        *func_name = fname;
    }

    return 0;
}

static inline char * mybpf_simple_get_prog_sec_name(FILE_MEM_S *m, int id)
{
    char *sec_name;

    if (_mybpf_simple_get_prog_names(m, id, &sec_name, NULL) < 0) {
        return NULL;
    }

    return sec_name;
}

static inline char * mybpf_simple_get_prog_func_name(FILE_MEM_S *m, int id)
{
    char *func_name;

    if (_mybpf_simple_get_prog_names(m, id, NULL, &func_name) < 0) {
        return NULL;
    }

    return func_name;
}

static inline int mybpf_simple_get_progs_size(FILE_MEM_S *m)
{
    void *sec = mybpf_simple_get_type_sec(m, MYBPF_SIMPLE_SEC_TYPE_PROG, 0);
    return mybpf_simple_get_sec_data_size(sec);
}

static inline void * mybpf_simple_get_progs(FILE_MEM_S *m)
{
    void *sec = mybpf_simple_get_type_sec(m, MYBPF_SIMPLE_SEC_TYPE_PROG, 0);
    return mybpf_simple_get_sec_data(sec);
}

static inline int mybpf_simple_get_map_count(FILE_MEM_S *m)
{
    MYBPF_SIMPLE_MAP_HDR_S *hdr = mybpf_simple_get_type_sec(m, MYBPF_SIMPLE_SEC_TYPE_MAP, 0);
    if (! hdr) {
        return 0;
    }

    return hdr->map_count;
}

static inline char * mybpf_simple_get_map_name(FILE_MEM_S *m, int id)
{
    int i;
    char *map_name;

    MYBPF_SIMPLE_MAP_NAME_HDR_S *name_hdr = mybpf_simple_get_type_sec(m, MYBPF_SIMPLE_SEC_TYPE_MAP_NAME, 0);
    if (! name_hdr) {
        return NULL;
    }

    if (id >= name_hdr->map_count) {
        return NULL;
    }

    map_name = mybpf_simple_get_sec_data(name_hdr);

    for (i=0; i<id; i++) {
        map_name = map_name + strlen(map_name) + 1;
    }

    return map_name;
}


#ifdef __cplusplus
}
#endif
#endif 
