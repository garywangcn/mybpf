/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0
* Description:
******************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include "bs.h"
#include "utl/mybpf_bare.h"

typedef struct {
    U8 *data; /* 文件数据 */
    U64 len;   /* 文件长度 */
}LLDATA_S;

void * MMAP_Create(int size)
{
    U8 *code = NULL;

    code = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (code == MAP_FAILED) {
        return NULL;
    }

    return code;
}

/* head_size: 保留的head size大小 */
void * MMAP_Map(void *buf, int buf_size, int head_size)
{
    U8 *code = NULL;
    int total_size = buf_size + head_size;

    code = MMAP_Create(total_size);
    if (code)  {
        memcpy(code + head_size, buf, buf_size);
    }

    return code;
}

void MMAP_Unmap(void *buf, int size)
{
    munmap(buf, size);
}

int MMAP_MakeExe(void *buf, int size)
{
    if (mprotect(buf, size, PROT_READ | PROT_EXEC) < 0) {
        return -1;
    }

    return 0;
}

S64 FILE_GetFileSize(void *fp)
{
    S64 cur = ftell(fp);
    if (cur < 0) {
        return -1;
    }

    if (fseek(fp, 0, SEEK_END) < 0) {
        return -1;
    }

    S64 size = ftell(fp);

    fseek(fp, cur, SEEK_SET);

    return size;
}

int FILE_Mem(char *filename, LLDATA_S *m)
{
    FILE *fp;
    S64 filesize;

    fp = fopen(filename, "rb");
    if (! fp) {
        goto _ERR;
    }

    filesize = FILE_GetFileSize(fp);
    if (filesize < 0) {
        goto _ERR;
    }

    m->len = filesize;
    m->data = malloc(filesize);
    if (! m->data) {
        goto _ERR;
    }

    if (filesize != fread(m->data, 1, filesize, fp)) {
        goto _ERR;
    }

    fclose(fp);

    return 0;

_ERR:
    if (fp) {
        fclose(fp);
    }
    if (m->data) {
        free(m->data);
    }
    return -1;
}

/* ./user_example filename */
int main(int argc, char **argv)
{
    LLDATA_S m = {0};
    MYBPF_PARAM_S p = {0};

    if (argc < 2) {
        printf("Usage: %s filename\n", argv[0]);
        return -1;
    }

    if (FILE_Mem(argv[1], &m) < 0) {
        return -1;
    }

    p.p[0] = argc;
    p.p[1] = (long)argv;

    MYBPF_RunBare(m.data, m.len, NULL, &p);

    return 0;
}

