/* Added by lixg */

#include <common.h>
#include <command.h>
#include <display_options.h>
#include <timestamp.h>
#include <version.h>
#include <version_string.h>
#include <linux/compiler.h>
#ifdef CONFIG_SYS_COREBOOT
#include <asm/cb_sysinfo.h>
#endif

#include <vsprintf.h>
#include "bs.h"
#include "utl/mybpf_bare.h"
#include "utl/mybpf_loader_def.h"
#include "utl/mybpf_spf_def.h"
#include "utl/mybpf_hookpoint_def.h"

static MYBPF_BARE_S g_spfloader;

static U64 _do_spf_cmd(int cmd, U64 p1, U64 p2, U64 p3, U64 p4)
{
    MYBPF_PARAM_S p;

    if (! g_spfloader.prog) {
        fprintf(stderr, "Error: spf loader not loaded \n");
        return -1;
    }

    p.p[0] = cmd;
    p.p[1] = p1;
    p.p[2] = p2;
    p.p[3] = p3;
    p.p[4] = p4;

    return MYBPF_RunBare(&g_spfloader, NULL, &p);
}

static int do_load_spfloader(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
    void *mem;

    if (argc < 2) {
        return CMD_RET_USAGE;
    }

	mem = (void*)hextoul(argv[1], NULL);

    int ret = MYBPF_LoadBare(mem, NULL, &g_spfloader);
    if (ret < 0) {
        printf("Load loader failed \n");
        return ret;
    }

    return _do_spf_cmd(SPF_CMD_INIT, 0, 0, 0, 0);
}

static int do_load_spf(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
    MYBPF_LOADER_PARAM_S p = {0};

    if (argc < 3) {
		return CMD_RET_USAGE;
    }

    p.instance = argv[1];
    p.flag = MYBPF_LOADER_FLAG_AUTO_ATTACH;
    p.simple_mem.data = (void*)hextoul(argv[2], NULL);

    int ret = _do_spf_cmd(SPF_CMD_LOAD, (long)&p, 0, 0, 0);
    if (ret < 0) {
        printf("Load spf failed \n");
        return ret;
    }

    return 0;
}

static int do_unload_spf(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
    if (argc < 2) {
        return CMD_RET_USAGE;
    }

    return _do_spf_cmd(SPF_CMD_UNLOAD, (long)argv[1], 0, 0, 0);
}

static int do_unload_all_spf(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
    return _do_spf_cmd(SPF_CMD_UNLOAD_ALL, 0, 0, 0, 0);
}

static int do_test_spf(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
    MYBPF_PARAM_S p = {0};
    p.p[0] = argc - 1;
    p.p[1] = (long)(argv + 1);
    return _do_spf_cmd(SPF_CMD_RUN, MYBPF_HP_TCMD, (long)&p, 0, 0);
}

U_BOOT_CMD(load_loader, 2, 0, do_load_spfloader, "load_loader", "address");
U_BOOT_CMD(load_spf, 3, 0, do_load_spf, "load_spf", "instance address");
U_BOOT_CMD(unload_spf, 2, 0, do_unload_spf, "unload_spf", "instance");
U_BOOT_CMD(unload_allspf, 1, 0, do_unload_all_spf, "unload_allspf", "");
U_BOOT_CMD(test_spf, 6, 0, do_test_spf, "test_spf", "args");

