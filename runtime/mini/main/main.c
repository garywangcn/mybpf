/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0
* Description:
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "bs.h"
#include "utl/mybpf_bare.h"

int FILE_Mem(char *filename, void **data)
{
    int fd;
    fd=open(filename, O_RDWR);
    if (fd < 0) {
        return fd;
    }

    struct stat st;
    int r = fstat(fd, &st);
    if (r < 0) {
        close(fd);
        return r;
    }

    void *p = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);    
    if ((p == NULL) || (p==(void*)-1)) {
        close(fd);
        return -1;
    }

    *data = p;

    return st.st_size;
}

/* ./user_example filename */
int main(int argc, char **argv)
{
    MYBPF_PARAM_S p = {0};
    void *data;
    int len;

    if (argc < 2) {
        printf("Usage: %s filename\n", argv[0]);
        return -1;
    }

    len = FILE_Mem(argv[1], &data);
    if (len <= 0) {
        return -1;
    }

    p.p[0] = argc;
    p.p[1] = (long)argv;

    MYBPF_RunBare(data, NULL, &p);

    munmap(data, len);

    return 0;
}

