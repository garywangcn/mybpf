/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0
* Description:
******************************************************************************/
#include "bs.h"
#include "utl/txt_utl.h"
#include "utl/vbuf_utl.h"
#include "utl/elf_utl.h"
#include "utl/mybpf_simple.h"

static int _mybpf_merge_file_to_vbuf(char *file1, char *file2,
        VBUF_S *src1, VBUF_S *src2, OUT VBUF_S *dst)
{
    int ret;

    ret = VBUF_ReadFile(file1, src1);
    if (ret < 0) {
        return ret;
    }

    ret = VBUF_ReadFile(file2, src2);
    if (ret < 0) {
        return ret;
    }

    return MYBPF_SIMPLE_Merge(src1, src2, dst);
}

static int _mybpf_merge_files(char *file1, char *file2, char *output_name)
{
    VBUF_S src1, src2, dst;
    int ret;

    VBUF_Init(&src1);
    VBUF_Init(&src2);
    VBUF_Init(&dst);

    ret = _mybpf_merge_file_to_vbuf(file1, file2, &src1, &src2, &dst);
    if (ret < 0) {
        goto _OUT;
    }

    ret = VBUF_WriteFile(output_name, &dst);

_OUT:
    VBUF_Finit(&src1);
    VBUF_Finit(&src2);
    VBUF_Finit(&dst);
    return ret;
}

int MYBPF_Merge(char *file1, char *file2, char *output_name)
{
    return _mybpf_merge_files(file1, file2, output_name);
}

