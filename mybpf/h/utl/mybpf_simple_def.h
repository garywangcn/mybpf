/*********************************************************
*   Copyright (C) LiXingang
*   Description: 
*
********************************************************/
#ifndef _MYBPF_SIMPLE_DEF_H
#define _MYBPF_SIMPLE_DEF_H
#ifdef __cplusplus
extern "C"
{
#endif

#define MYBPF_SIMPLE_VER 0 
#define MYBPF_SIMPLE_MAGIC 0x6670737f

enum {
    MYBPF_SIMPLE_SEC_TYPE_UNUSED = 0, 
    MYBPF_SIMPLE_SEC_TYPE_MAP, 
    MYBPF_SIMPLE_SEC_TYPE_MAP_NAME, 
    MYBPF_SIMPLE_SEC_TYPE_PROG, 
    MYBPF_SIMPLE_SEC_TYPE_PROG_INFO, 
    MYBPF_SIMPLE_SEC_TYPE_GLOBAL_DATA,  
    MYBPF_SIMPLE_SEC_TYPE_PRIVATE, 
    MYBPF_SIMPLE_SEC_TYPE_HELPER_DEPENDS, 
};

typedef struct {
    UINT magic;
    UCHAR ver;       
    UCHAR reserved[3];
    UINT totle_size;
}MYBPF_SIMPLE_HDR_S;

typedef struct {
    UINT sec_size; 
    UCHAR sec_type;
    UCHAR name_size; 

    UCHAR resereved[2];
}MYBPF_SIMPLE_COMMON_HDR_S;

typedef struct {
    UINT sec_size; 
    UCHAR sec_type;
    UCHAR name_size; 

    UCHAR map_count; 
    UCHAR reserved2;
}MYBPF_SIMPLE_MAP_HDR_S;

typedef struct {
    UINT sec_size; 
    UCHAR sec_type;
    UCHAR name_size; 

    UCHAR map_index; 
    UCHAR reserved;
}MYBPF_SIMPLE_MAP_DATA_S;

typedef struct {
    UINT sec_size; 
    UCHAR sec_type;
    UCHAR name_size; 

    UCHAR map_count; 
    UCHAR reserved;
}MYBPF_SIMPLE_MAP_NAME_HDR_S;

typedef struct {
    UINT sec_size; 
    UCHAR sec_type;
    UCHAR name_size; 

    UCHAR jit_arch;
    UCHAR reserved;
}MYBPF_SIMPLE_PROG_HDR_S;

typedef struct {
    UINT offset;
    UINT len;
}MYBPF_SIMPLE_PROG_OFF_S;

typedef struct {
    UINT sec_size; 
    UCHAR sec_type;
    UCHAR name_size; 

    USHORT func_count;
}MYBPF_SIMPLE_PROG_INFO_HDR_S;

typedef struct {
    UINT sec_size; 
    UCHAR sec_type;
    UCHAR name_size; 

    UCHAR reserved1;
    UCHAR reserved2;
}MYBPF_SIMPLE_PRIVATE_HDR_S;

typedef struct {
    UINT sec_size;
    UCHAR sec_type;
    UCHAR name_size; 

    UCHAR reserved;
    UCHAR reserved2;
}MYBPF_SIMPLE_HELPER_DENENDS_HDR_S;

#ifdef __cplusplus
}
#endif
#endif 
