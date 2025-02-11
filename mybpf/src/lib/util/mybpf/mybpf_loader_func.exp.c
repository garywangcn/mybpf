#include "bs.h" 
#include "utl/mybpf_regs.h" 
#include "utl/mybpf_asmdef.h" 
#include "utl/bpfasm_utl.h" 

static MYBPF_INSN_S g_bpfasm_insts[] = { 

    BPF_MOV64_REG(BPF_R6, BPF_R1), 
    BPF_LDX_MEM(BPF_W, BPF_R1, BPF_R2, 128), 
    BPF_ALU64_IMM(BPF_RSH, BPF_R1, 16), 
    BPF_STX_MEM(BPF_B, BPF_R6, BPF_R1, 130), 
    BPF_LDX_MEM(BPF_W, BPF_R1, BPF_R2, 132), 
    BPF_STX_MEM(BPF_W, BPF_R6, BPF_R1, 132), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R2, 136), 
    BPF_MOV64_REG(BPF_R7, BPF_R6), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R7, 136), 
    BPF_MOV64_REG(BPF_R1, BPF_R7), 
    BPF_MOV64_IMM(BPF_R3, 256), 
    BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, 1000040), 
    BPF_LDX_MEM(BPF_W, BPF_R1, BPF_R6, 128), 
    BPF_ALU64_IMM(BPF_AND, BPF_R1, 16711680), 
    BPF_JMP_IMM(BPF_JEQ, BPF_R1, 0, 11), 
    BPF_MOV64_IMM(BPF_R1, 0), 
    BPF_LDX_MEM(BPF_DW, BPF_R2, BPF_R7, 0), 
    BPF_LDX_MEM(BPF_W, BPF_R3, BPF_R2, 128), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R3, 1), 
    BPF_STX_MEM(BPF_W, BPF_R2, BPF_R3, 128), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R7, 8), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R1, 1), 
    BPF_LDX_MEM(BPF_W, BPF_R2, BPF_R6, 128), 
    BPF_ALU64_IMM(BPF_RSH, BPF_R2, 16), 
    BPF_ALU64_IMM(BPF_AND, BPF_R2, 255), 
    BPF_JMP_REG(BPF_JGT, BPF_R2, BPF_R1, -10), 
    BPF_EXIT_INSN(), 

    BPF_MOV64_REG(BPF_R9, BPF_R2), 
    BPF_MOV64_IMM(BPF_R1, 116), 
    BPF_STX_MEM(BPF_H, BPF_R10, BPF_R1, -28), 
    BPF_MOV64_IMM(BPF_R1, 2019914798), 
    BPF_STX_MEM(BPF_W, BPF_R10, BPF_R1, -32), 
    BPF_MOV64_IMM(BPF_R7, 0), 
    BPF_LDX_MEM(BPF_W, BPF_R1, BPF_R9, 912), 
    BPF_ALU64_IMM(BPF_LSH, BPF_R1, 32), 
    BPF_ALU64_IMM(BPF_ARSH, BPF_R1, 32), 
    BPF_MOV64_IMM(BPF_R2, 1), 
    BPF_JMP_REG(BPF_JSGT, BPF_R2, BPF_R1, 31), 
    BPF_MOV64_IMM(BPF_R6, 0), 
    BPF_MOV64_IMM(BPF_R8, 0), 
    BPF_STX_MEM(BPF_DW, BPF_R10, BPF_R9, -80), 
    BPF_JMP_A(29), 
    BPF_MOV64_REG(BPF_R1, BPF_R7), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R1, 144), 
    BPF_LDX_MEM(BPF_DW, BPF_R2, BPF_R10, -48), 
    BPF_MOV64_IMM(BPF_R3, 64), 
    BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, 1000012), 
    BPF_STX_MEM(BPF_DW, BPF_R7, BPF_R9, 224), 
    BPF_LDX_MEM(BPF_DW, BPF_R1, BPF_R10, -64), 
    BPF_STX_MEM(BPF_W, BPF_R7, BPF_R1, 220), 
    BPF_LDX_MEM(BPF_DW, BPF_R9, BPF_R10, -80), 
    BPF_STX_MEM(BPF_DW, BPF_R7, BPF_R9, 208), 
    BPF_ALU64_IMM(BPF_LSH, BPF_R8, 3), 
    BPF_MOV64_REG(BPF_R1, BPF_R9), 
    BPF_ALU64_REG(BPF_ADD, BPF_R1, BPF_R8), 
    BPF_STX_MEM(BPF_DW, BPF_R1, BPF_R7, 656), 
    BPF_LDX_MEM(BPF_W, BPF_R1, BPF_R9, 128), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R1, 256), 
    BPF_ALU64_IMM(BPF_RSH, BPF_R1, 8), 
    BPF_STX_MEM(BPF_B, BPF_R9, BPF_R1, 129), 
    BPF_LDX_MEM(BPF_DW, BPF_R6, BPF_R10, -56), 
    BPF_LDX_MEM(BPF_DW, BPF_R8, BPF_R10, -40), 
    BPF_MOV64_IMM(BPF_R7, 0), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R6, 32), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R8, 1), 
    BPF_LDX_MEM(BPF_W, BPF_R1, BPF_R9, 912), 
    BPF_ALU64_IMM(BPF_LSH, BPF_R1, 32), 
    BPF_ALU64_IMM(BPF_ARSH, BPF_R1, 32), 
    BPF_JMP_REG(BPF_JSGT, BPF_R1, BPF_R8, 2), 
    BPF_MOV64_REG(BPF_R0, BPF_R7), 
    BPF_EXIT_INSN(), 
    BPF_LDX_MEM(BPF_DW, BPF_R7, BPF_R9, 928), 
    BPF_ALU64_REG(BPF_ADD, BPF_R7, BPF_R6), 
    BPF_LDX_MEM(BPF_DW, BPF_R1, BPF_R7, 0), 
    BPF_MOV64_REG(BPF_R2, BPF_R10), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R2, -32), 
    BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, 1000011), 
    BPF_ALU64_IMM(BPF_LSH, BPF_R0, 32), 
    BPF_ALU64_IMM(BPF_RSH, BPF_R0, 32), 
    BPF_JMP_IMM(BPF_JEQ, BPF_R0, 0, -18), 
    BPF_LDX_MEM(BPF_DW, BPF_R2, BPF_R7, 8), 
    BPF_JMP_IMM(BPF_JNE, BPF_R2, 0, 18), 
    BPF_LD_IMM64_RAW(BPF_R1, BPF_R0, 0x656d616e206e6fLL), 
    BPF_STX_MEM(BPF_DW, BPF_R10, BPF_R1, -8), 
    BPF_LD_IMM64_RAW(BPF_R1, BPF_R0, 0x6974636e75662074LL), 
    BPF_STX_MEM(BPF_DW, BPF_R10, BPF_R1, -16), 
    BPF_LD_IMM64_RAW(BPF_R1, BPF_R0, 0x65672074276e6143LL), 
    BPF_STX_MEM(BPF_DW, BPF_R10, BPF_R1, -24), 
    BPF_LD_IMM64_RAW(BPF_R7, BPF_R0, 0xffffffffLL), 
    BPF_LD_IMM64_RAW(BPF_R1, BPF_R0, 0xffffffffLL), 
    BPF_MOV64_IMM(BPF_R2, 0), 
    BPF_MOV64_IMM(BPF_R3, 0), 
    BPF_MOV64_IMM(BPF_R4, 0), 
    BPF_MOV64_IMM(BPF_R5, 63), 
    BPF_JMP_A(49), 
    BPF_STX_MEM(BPF_DW, BPF_R10, BPF_R8, -40), 
    BPF_LDX_MEM(BPF_W, BPF_R8, BPF_R9, 128), 
    BPF_ALU64_IMM(BPF_RSH, BPF_R8, 8), 
    BPF_ALU64_IMM(BPF_AND, BPF_R8, 255), 
    BPF_MOV64_IMM(BPF_R1, 32), 
    BPF_JMP_REG(BPF_JGT, BPF_R1, BPF_R8, 19), 
    BPF_MOV64_IMM(BPF_R1, 114), 
    BPF_STX_MEM(BPF_H, BPF_R10, BPF_R1, -4), 
    BPF_MOV64_IMM(BPF_R1, 1700949365), 
    BPF_STX_MEM(BPF_W, BPF_R10, BPF_R1, -8), 
    BPF_LD_IMM64_RAW(BPF_R1, BPF_R0, 0x6e2078616d20676fLL), 
    BPF_STX_MEM(BPF_DW, BPF_R10, BPF_R1, -16), 
    BPF_LD_IMM64_RAW(BPF_R1, BPF_R0, 0x7270206863616552LL), 
    BPF_STX_MEM(BPF_DW, BPF_R10, BPF_R1, -24), 
    BPF_LD_IMM64_RAW(BPF_R7, BPF_R0, 0xffffffffLL), 
    BPF_LD_IMM64_RAW(BPF_R1, BPF_R0, 0xffffffffLL), 
    BPF_MOV64_IMM(BPF_R2, 0), 
    BPF_MOV64_IMM(BPF_R3, 0), 
    BPF_MOV64_IMM(BPF_R4, 0), 
    BPF_MOV64_IMM(BPF_R5, 67), 
    BPF_JMP_A(24), 
    BPF_STX_MEM(BPF_DW, BPF_R10, BPF_R2, -48), 
    BPF_STX_MEM(BPF_DW, BPF_R10, BPF_R6, -56), 
    BPF_LDX_MEM(BPF_DW, BPF_R1, BPF_R7, 0), 
    BPF_STX_MEM(BPF_DW, BPF_R10, BPF_R1, -72), 
    BPF_LDX_MEM(BPF_W, BPF_R1, BPF_R7, 24), 
    BPF_STX_MEM(BPF_DW, BPF_R10, BPF_R1, -64), 
    BPF_LDX_MEM(BPF_W, BPF_R6, BPF_R7, 20), 
    BPF_LDX_MEM(BPF_DW, BPF_R9, BPF_R9, 944), 
    BPF_MOV64_IMM(BPF_R1, 232), 
    BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, 1000000), 
    BPF_MOV64_REG(BPF_R7, BPF_R0), 
    BPF_JMP_IMM(BPF_JEQ, BPF_R7, 0, 17), 
    BPF_ALU64_REG(BPF_ADD, BPF_R9, BPF_R6), 
    BPF_MOV64_REG(BPF_R1, BPF_R7), 
    BPF_MOV64_IMM(BPF_R2, 0), 
    BPF_MOV64_IMM(BPF_R3, 232), 
    BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, 1000041), 
    BPF_LDX_MEM(BPF_DW, BPF_R2, BPF_R10, -72), 
    BPF_JMP_IMM(BPF_JEQ, BPF_R2, 0, -102), 
    BPF_MOV64_REG(BPF_R1, BPF_R7), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R1, 16), 
    BPF_MOV64_IMM(BPF_R3, 128), 
    BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, 1000012), 
    BPF_JMP_A(-107), 
    BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, 2000000), 
    BPF_MOV64_REG(BPF_R1, BPF_R10), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R1, -24), 
    BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, 2000001), 
    BPF_JMP_A(-85), 
    BPF_MOV64_IMM(BPF_R1, 658720), 
    BPF_STX_MEM(BPF_W, BPF_R10, BPF_R1, -8), 
    BPF_LD_IMM64_RAW(BPF_R1, BPF_R0, 0x73253a7325206461LL), 
    BPF_STX_MEM(BPF_DW, BPF_R10, BPF_R1, -16), 
    BPF_LD_IMM64_RAW(BPF_R1, BPF_R0, 0x6f6c2074276e6143LL), 
    BPF_STX_MEM(BPF_DW, BPF_R10, BPF_R1, -24), 
    BPF_LD_IMM64_RAW(BPF_R7, BPF_R0, 0xffffffffLL), 
    BPF_LD_IMM64_RAW(BPF_R1, BPF_R0, 0xffffffffLL), 
    BPF_MOV64_IMM(BPF_R2, 0), 
    BPF_MOV64_IMM(BPF_R3, 0), 
    BPF_MOV64_IMM(BPF_R4, 0), 
    BPF_MOV64_IMM(BPF_R5, 72), 
    BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, 2000000), 
    BPF_LDX_MEM(BPF_DW, BPF_R1, BPF_R10, -80), 
    BPF_LDX_MEM(BPF_DW, BPF_R2, BPF_R1, 8), 
    BPF_MOV64_REG(BPF_R1, BPF_R10), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R1, -24), 
    BPF_LDX_MEM(BPF_DW, BPF_R3, BPF_R10, -48), 
    BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, 2000001), 
    BPF_JMP_A(-109), 

    BPF_MOV64_IMM(BPF_R0, 0), 
    BPF_LDX_MEM(BPF_W, BPF_R1, BPF_R2, 8), 
    BPF_LDX_MEM(BPF_W, BPF_R4, BPF_R3, 128), 
    BPF_ALU64_IMM(BPF_RSH, BPF_R4, 16), 
    BPF_ALU64_IMM(BPF_AND, BPF_R4, 255), 
    BPF_JMP_REG(BPF_JNE, BPF_R1, BPF_R4, 42), 
    BPF_LDX_MEM(BPF_W, BPF_R4, BPF_R2, 4), 
    BPF_LDX_MEM(BPF_W, BPF_R5, BPF_R3, 132), 
    BPF_JMP_REG(BPF_JNE, BPF_R4, BPF_R5, 39), 
    BPF_MOV64_REG(BPF_R5, BPF_R1), 
    BPF_ALU64_IMM(BPF_LSH, BPF_R5, 32), 
    BPF_ALU64_IMM(BPF_ARSH, BPF_R5, 32), 
    BPF_MOV64_IMM(BPF_R0, 1), 
    BPF_JMP_REG(BPF_JSGT, BPF_R0, BPF_R5, 34), 
    BPF_MOV64_IMM(BPF_R5, 0), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R3, 136), 
    BPF_LDX_MEM(BPF_DW, BPF_R2, BPF_R2, 16), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R2, 8), 
    BPF_ALU64_IMM(BPF_LSH, BPF_R4, 32), 
    BPF_ALU64_IMM(BPF_ARSH, BPF_R4, 32), 
    BPF_LDX_MEM(BPF_DW, BPF_R6, BPF_R3, 0), 
    BPF_MOV64_IMM(BPF_R0, 0), 
    BPF_JMP_IMM(BPF_JEQ, BPF_R6, 0, 25), 
    BPF_LDX_MEM(BPF_W, BPF_R7, BPF_R6, 132), 
    BPF_LDX_MEM(BPF_W, BPF_R8, BPF_R2, -8), 
    BPF_MOV64_IMM(BPF_R0, 0), 
    BPF_JMP_REG(BPF_JNE, BPF_R8, BPF_R7, 21), 
    BPF_LDX_MEM(BPF_W, BPF_R7, BPF_R6, 144), 
    BPF_LDX_MEM(BPF_W, BPF_R8, BPF_R2, 4), 
    BPF_MOV64_IMM(BPF_R0, 0), 
    BPF_JMP_REG(BPF_JNE, BPF_R8, BPF_R7, 17), 
    BPF_LDX_MEM(BPF_W, BPF_R7, BPF_R6, 148), 
    BPF_LDX_MEM(BPF_W, BPF_R8, BPF_R2, 8), 
    BPF_MOV64_IMM(BPF_R0, 0), 
    BPF_JMP_REG(BPF_JNE, BPF_R8, BPF_R7, 13), 
    BPF_LDX_MEM(BPF_W, BPF_R7, BPF_R6, 136), 
    BPF_LDX_MEM(BPF_W, BPF_R8, BPF_R2, -4), 
    BPF_MOV64_IMM(BPF_R0, 0), 
    BPF_JMP_REG(BPF_JNE, BPF_R8, BPF_R7, 9), 
    BPF_LDX_MEM(BPF_W, BPF_R6, BPF_R6, 140), 
    BPF_LDX_MEM(BPF_W, BPF_R7, BPF_R2, 0), 
    BPF_MOV64_IMM(BPF_R0, 0), 
    BPF_JMP_REG(BPF_JNE, BPF_R7, BPF_R6, 5), 
    BPF_ALU64_REG(BPF_ADD, BPF_R2, BPF_R4), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R3, 8), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R5, 1), 
    BPF_MOV64_IMM(BPF_R0, 1), 
    BPF_JMP_REG(BPF_JGT, BPF_R1, BPF_R5, -28), 
    BPF_EXIT_INSN(), 

    BPF_MOV64_REG(BPF_R6, BPF_R1), 
    BPF_MOV64_REG(BPF_R1, BPF_R2), 
    BPF_MOV64_REG(BPF_R2, BPF_R3), 
    BPF_MOV64_IMM(BPF_R3, 8), 
    BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, 1000500), 
    BPF_STX_MEM(BPF_DW, BPF_R6, BPF_R0, 936), 
    BPF_JMP_IMM(BPF_JNE, BPF_R0, 0, 26), 
    BPF_MOV64_IMM(BPF_R1, 1936158578), 
    BPF_STX_MEM(BPF_W, BPF_R10, BPF_R1, -8), 
    BPF_LD_IMM64_RAW(BPF_R1, BPF_R0, 0x7020726f66207972LL), 
    BPF_STX_MEM(BPF_DW, BPF_R10, BPF_R1, -16), 
    BPF_LD_IMM64_RAW(BPF_R1, BPF_R0, 0x6f6d656d20636f6cLL), 
    BPF_STX_MEM(BPF_DW, BPF_R10, BPF_R1, -24), 
    BPF_LD_IMM64_RAW(BPF_R1, BPF_R0, 0x6c612074276e6143LL), 
    BPF_STX_MEM(BPF_DW, BPF_R10, BPF_R1, -32), 
    BPF_MOV64_IMM(BPF_R1, 0), 
    BPF_STX_MEM(BPF_B, BPF_R10, BPF_R1, -4), 
    BPF_LD_IMM64_RAW(BPF_R6, BPF_R0, 0xffffffffLL), 
    BPF_LD_IMM64_RAW(BPF_R1, BPF_R0, 0xffffffffLL), 
    BPF_MOV64_IMM(BPF_R2, 0), 
    BPF_MOV64_IMM(BPF_R3, 0), 
    BPF_MOV64_IMM(BPF_R4, 0), 
    BPF_MOV64_IMM(BPF_R5, 172), 
    BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, 2000000), 
    BPF_MOV64_REG(BPF_R1, BPF_R10), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R1, -32), 
    BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, 2000001), 
    BPF_JMP_A(15), 
    BPF_MOV64_REG(BPF_R1, BPF_R6), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R1, 952), 
    BPF_STX_MEM(BPF_DW, BPF_R0, BPF_R1, 0), 
    BPF_MOV64_REG(BPF_R1, BPF_R0), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R1, 8), 
    BPF_STX_MEM(BPF_DW, BPF_R6, BPF_R1, 944), 
    BPF_LDX_MEM(BPF_W, BPF_R1, BPF_R6, 128), 
    BPF_ALU64_IMM(BPF_OR, BPF_R1, 1), 
    BPF_STX_MEM(BPF_W, BPF_R6, BPF_R1, 128), 
    BPF_LDX_MEM(BPF_W, BPF_R2, BPF_R6, 920), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R2, 8), 
    BPF_STX_MEM(BPF_W, BPF_R6, BPF_R2, 916), 
    BPF_MOV64_REG(BPF_R1, BPF_R0), 
    BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, 1000502), 
    BPF_MOV64_IMM(BPF_R6, 0), 
    BPF_MOV64_REG(BPF_R0, BPF_R6), 
    BPF_EXIT_INSN(), 

    BPF_MOV64_REG(BPF_R6, BPF_R3), 
    BPF_MOV64_REG(BPF_R8, BPF_R1), 
    BPF_MOV64_REG(BPF_R1, BPF_R2), 
    BPF_MOV64_REG(BPF_R2, BPF_R6), 
    BPF_MOV64_IMM(BPF_R3, 8), 
    BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, 1000500), 
    BPF_MOV64_REG(BPF_R7, BPF_R0), 
    BPF_MOV64_IMM(BPF_R0, 0), 
    BPF_JMP_IMM(BPF_JEQ, BPF_R7, 0, 7), 
    BPF_STX_MEM(BPF_DW, BPF_R7, BPF_R8, 0), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R6, 8), 
    BPF_MOV64_REG(BPF_R1, BPF_R7), 
    BPF_MOV64_REG(BPF_R2, BPF_R6), 
    BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, 1000502), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R7, 8), 
    BPF_MOV64_REG(BPF_R0, BPF_R7), 
    BPF_EXIT_INSN(), 

    BPF_ALU64_IMM(BPF_ADD, BPF_R1, -8), 
    BPF_ALU64_IMM(BPF_ADD, BPF_R2, 8), 
    BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, 1000501), 
    BPF_EXIT_INSN(), 
}; 

U64 _MYBPF_LOADER_CopyMapsFd(U64 p1, U64 p2, U64 p3, U64 p4, U64 p5) 
{ 
    MYBPF_PARAM_S p; 
    MYBPF_CTX_S ctx = {0}; 

    ctx.begin_addr = g_bpfasm_insts; 
    ctx.end_addr = (char*)(void*)g_bpfasm_insts + sizeof(g_bpfasm_insts); 
    ctx.insts = (char*)g_bpfasm_insts; 
    p.p[0]=p1; p.p[1]=p2; p.p[2]=p3; p.p[3]=p4; p.p[4]=p5; 
    int ret = MYBPF_DefultRun(&ctx, &p); 
    if (ret < 0) return ret; 
    return ctx.bpf_ret; 
} 

U64 _MYBPF_LOADER_LoadProgs(U64 p1, U64 p2, U64 p3, U64 p4, U64 p5) 
{ 
    MYBPF_PARAM_S p; 
    MYBPF_CTX_S ctx = {0}; 

    ctx.begin_addr = g_bpfasm_insts; 
    ctx.end_addr = (char*)(void*)g_bpfasm_insts + sizeof(g_bpfasm_insts); 
    ctx.insts = (char*)g_bpfasm_insts + 216; 
    p.p[0]=p1; p.p[1]=p2; p.p[2]=p3; p.p[3]=p4; p.p[4]=p5; 
    int ret = MYBPF_DefultRun(&ctx, &p); 
    if (ret < 0) return ret; 
    return ctx.bpf_ret; 
} 

U64 _MYBPF_LOADER_CheckMayKeepMap(U64 p1, U64 p2, U64 p3, U64 p4, U64 p5) 
{ 
    MYBPF_PARAM_S p; 
    MYBPF_CTX_S ctx = {0}; 

    ctx.begin_addr = g_bpfasm_insts; 
    ctx.end_addr = (char*)(void*)g_bpfasm_insts + sizeof(g_bpfasm_insts); 
    ctx.insts = (char*)g_bpfasm_insts + 1424; 
    p.p[0]=p1; p.p[1]=p2; p.p[2]=p3; p.p[3]=p4; p.p[4]=p5; 
    int ret = MYBPF_DefultRun(&ctx, &p); 
    if (ret < 0) return ret; 
    return ctx.bpf_ret; 
} 

U64 _MYBPF_LOADER_MakeExe(U64 p1, U64 p2, U64 p3, U64 p4, U64 p5) 
{ 
    MYBPF_PARAM_S p; 
    MYBPF_CTX_S ctx = {0}; 

    ctx.begin_addr = g_bpfasm_insts; 
    ctx.end_addr = (char*)(void*)g_bpfasm_insts + sizeof(g_bpfasm_insts); 
    ctx.insts = (char*)g_bpfasm_insts + 1816; 
    p.p[0]=p1; p.p[1]=p2; p.p[2]=p3; p.p[3]=p4; p.p[4]=p5; 
    int ret = MYBPF_DefultRun(&ctx, &p); 
    if (ret < 0) return ret; 
    return ctx.bpf_ret; 
} 

U64 _MYBPF_MakeExe(U64 p1, U64 p2, U64 p3, U64 p4, U64 p5) 
{ 
    MYBPF_PARAM_S p; 
    MYBPF_CTX_S ctx = {0}; 

    ctx.begin_addr = g_bpfasm_insts; 
    ctx.end_addr = (char*)(void*)g_bpfasm_insts + sizeof(g_bpfasm_insts); 
    ctx.insts = (char*)g_bpfasm_insts + 2216; 
    p.p[0]=p1; p.p[1]=p2; p.p[2]=p3; p.p[3]=p4; p.p[4]=p5; 
    int ret = MYBPF_DefultRun(&ctx, &p); 
    if (ret < 0) return ret; 
    return ctx.bpf_ret; 
} 

U64 _MYBPF_UnmapExe(U64 p1, U64 p2, U64 p3, U64 p4, U64 p5) 
{ 
    MYBPF_PARAM_S p; 
    MYBPF_CTX_S ctx = {0}; 

    ctx.begin_addr = g_bpfasm_insts; 
    ctx.end_addr = (char*)(void*)g_bpfasm_insts + sizeof(g_bpfasm_insts); 
    ctx.insts = (char*)g_bpfasm_insts + 2352; 
    p.p[0]=p1; p.p[1]=p2; p.p[2]=p3; p.p[3]=p4; p.p[4]=p5; 
    int ret = MYBPF_DefultRun(&ctx, &p); 
    if (ret < 0) return ret; 
    return ctx.bpf_ret; 
} 

