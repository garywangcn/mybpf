/******************************************************************************
* Copyright (C), Xingang.Li
* Author:      Xingang.Li  Version: 1.0
* Description:
******************************************************************************/
#ifndef _MYBPF_JIT_X86_64_H
#define _MYBPF_JIT_X86_64_H

#define RAX 0
#define RCX 1
#define RDX 2
#define RBX 3
#define RSP 4
#define RBP 5
#define RIP 5
#define RSI 6
#define RDI 7
#define R8 8
#define R9 9
#define R10 10
#define R11 11
#define R12 12
#define R13 13
#define R14 14
#define R15 15

enum operand_size
{
    SIZE_8,
    SIZE_16,
    SIZE_32,
    SIZE_64,
};

static inline void
emit_bytes(struct jit_state* state, void* data, uint32_t len)
{
    assert(state->offset <= state->size - len);
    if ((state->offset + len) > state->size) {
        state->offset = state->size;
        return;
    }
    memcpy(state->buf + state->offset, data, len);
    state->offset += len;
}

static inline void
emit1(struct jit_state* state, uint8_t x)
{
    emit_bytes(state, &x, sizeof(x));
}

static inline void
emit2(struct jit_state* state, uint16_t x)
{
    emit_bytes(state, &x, sizeof(x));
}

static inline void
emit4(struct jit_state* state, uint32_t x)
{
    emit_bytes(state, &x, sizeof(x));
}

static inline void
emit8(struct jit_state* state, uint64_t x)
{
    emit_bytes(state, &x, sizeof(x));
}

static inline void
emit_jump_offset(struct jit_state* state, int32_t target_pc)
{
    if (state->num_jumps == MYBPF_JIT_MAX_INSTS) {
        return;
    }
    struct jump* jump = &state->jumps[state->num_jumps++];
    jump->offset_loc = state->offset;
    jump->target_pc = target_pc;
    emit4(state, 0);
}

static inline void
emit_modrm(struct jit_state* state, int mod, int r, int m)
{
    assert(!(mod & ~0xc0));
    emit1(state, (mod & 0xc0) | ((r & 7) << 3) | (m & 7));
}

static inline void
emit_modrm_reg2reg(struct jit_state* state, int r, int m)
{
    emit_modrm(state, 0xc0, r, m);
}

static inline void
emit_modrm_and_displacement(struct jit_state* state, int r, int m, int32_t d)
{
    if (d == 0 && (m & 7) != RBP) {
        emit_modrm(state, 0x00, r, m);
    } else if (d >= -128 && d <= 127) {
        emit_modrm(state, 0x40, r, m);
        emit1(state, d);
    } else {
        emit_modrm(state, 0x80, r, m);
        emit4(state, d);
    }
}

static inline void
emit_rex(struct jit_state* state, int w, int r, int x, int b)
{
    assert(!(w & ~1));
    assert(!(r & ~1));
    assert(!(x & ~1));
    assert(!(b & ~1));
    emit1(state, 0x40 | (w << 3) | (r << 2) | (x << 1) | b);
}


static inline void
emit_basic_rex(struct jit_state* state, int w, int src, int dst)
{
    if (w || (src & 8) || (dst & 8)) {
        emit_rex(state, w, !!(src & 8), 0, !!(dst & 8));
    }
}

static inline void
emit_push(struct jit_state* state, int r)
{
    emit_basic_rex(state, 0, 0, r);
    emit1(state, 0x50 | (r & 7));
}

static inline void
emit_pop(struct jit_state* state, int r)
{
    emit_basic_rex(state, 0, 0, r);
    emit1(state, 0x58 | (r & 7));
}




static inline void
emit_alu32(struct jit_state* state, int op, int src, int dst)
{
    emit_basic_rex(state, 0, src, dst);
    emit1(state, op);
    emit_modrm_reg2reg(state, src, dst);
}


static inline void
emit_alu32_imm32(struct jit_state* state, int op, int src, int dst, int32_t imm)
{
    emit_alu32(state, op, src, dst);
    emit4(state, imm);
}


static inline void
emit_alu32_imm8(struct jit_state* state, int op, int src, int dst, int8_t imm)
{
    emit_alu32(state, op, src, dst);
    emit1(state, imm);
}




static inline void
emit_alu64(struct jit_state* state, int op, int src, int dst)
{
    emit_basic_rex(state, 1, src, dst);
    emit1(state, op);
    emit_modrm_reg2reg(state, src, dst);
}


static inline void
emit_alu64_imm32(struct jit_state* state, int op, int src, int dst, int32_t imm)
{
    emit_alu64(state, op, src, dst);
    emit4(state, imm);
}


static inline void
emit_alu64_imm8(struct jit_state* state, int op, int src, int dst, int8_t imm)
{
    emit_alu64(state, op, src, dst);
    emit1(state, imm);
}

static inline int _mybpf_jit_x86_get_state_offset(struct jit_state* state)
{
    return state->offset;
}


static inline void
emit_mov(struct jit_state* state, int src, int dst)
{
    emit_alu64(state, 0x89, src, dst);
}

static inline void
emit_cmp_imm32(struct jit_state* state, int dst, int32_t imm)
{
    emit_alu64_imm32(state, 0x81, 7, dst, imm);
}

static inline void
emit_cmp32_imm32(struct jit_state* state, int dst, int32_t imm)
{
    emit_alu32_imm32(state, 0x81, 7, dst, imm);
}

static inline void
emit_cmp(struct jit_state* state, int src, int dst)
{
    emit_alu64(state, 0x39, src, dst);
}

static inline void
emit_cmp32(struct jit_state* state, int src, int dst)
{
    emit_alu32(state, 0x39, src, dst);
}

static inline void
emit_jcc(struct jit_state* state, int code, int32_t target_pc)
{
    emit1(state, 0x0f);
    emit1(state, code);
    emit_jump_offset(state, target_pc);
}


static inline void
emit_load(struct jit_state* state, enum operand_size size, int src, int dst, int32_t offset)
{
    emit_basic_rex(state, size == SIZE_64, dst, src);

    if (size == SIZE_8|| size == SIZE_16) {
        
        emit1(state, 0x0f);
        emit1(state, size == SIZE_8 ? 0xb6 : 0xb7);
    } else if (size == SIZE_32 || size == SIZE_64) {
        
        emit1(state, 0x8b);
    }

    emit_modrm_and_displacement(state, dst, src, offset);
}


static inline void
emit_lea(struct jit_state* state, int src, int dst, int32_t offset)
{
    if (dst & 8) {
        emit1(state, 0x4c);
    } else {
        emit1(state, 0x48);
    }

    emit1(state, 0x8d);

    dst &= 0x7;

    emit1(state, (dst << 3) | src);

    emit4(state, offset);

}


static inline void 
emit_load_imm(struct jit_state* state, int dst, int64_t imm)
{
    if (imm >= INT32_MIN && imm <= INT32_MAX) {
        emit_alu64_imm32(state, 0xc7, 0, dst, imm);
    } else {
        
        emit_basic_rex(state, 1, 0, dst);
        emit1(state, 0xb8 | (dst & 7));
        emit8(state, imm);
    }
}


static inline void
emit_store(struct jit_state* state, enum operand_size size, int src, int dst, int32_t offset)
{
    if (size == SIZE_16) {
        emit1(state, 0x66); 
    }
    int rexw = size == SIZE_64;
    if (rexw || src & 8 || dst & 8 || size == SIZE_8) {
        emit_rex(state, rexw, !!(src & 8), 0, !!(dst & 8));
    }
    emit1(state, size == SIZE_8 ? 0x88 : 0x89);
    emit_modrm_and_displacement(state, src, dst, offset);
}


static inline void
emit_store_imm32(struct jit_state* state, enum operand_size size, int dst, int32_t offset, int32_t imm)
{
    if (size == SIZE_16) {
        emit1(state, 0x66); 
    }
    emit_basic_rex(state, size == SIZE_64, 0, dst);
    emit1(state, size == SIZE_8 ? 0xc6 : 0xc7);
    emit_modrm_and_displacement(state, 0, dst, offset);
    if (size == SIZE_32 || size == SIZE_64) {
        emit4(state, imm);
    } else if (size == SIZE_16) {
        emit2(state, imm);
    } else if (size == SIZE_8) {
        emit1(state, imm);
    }
}

static inline void
emit_call(struct jit_state* state, void* target)
{
#if defined(_WIN32)
    
    emit_push(state, map_register(5));

    
    
    emit_alu64_imm32(state, 0x81, 5, RSP, 4 * sizeof(uint64_t));
#endif

    
    emit_load_imm(state, RAX, (long)target);
    
    emit1(state, 0xff);
    emit1(state, 0xd0);

#if defined(_WIN32)
    
    emit_alu64_imm32(state, 0x81, 0, RSP, 5 * sizeof(uint64_t));
#endif
}

static inline void
emit_call_by_reg(struct jit_state* state, int reg)
{
#if defined(_WIN32)
    
    emit_push(state, map_register(5));

    
    
    emit_alu64_imm32(state, 0x81, 5, RSP, 4 * sizeof(uint64_t));
#endif

    if (reg != RAX) {
        emit_mov(state, reg, RAX);
    }

    
    emit1(state, 0xff);
    emit1(state, 0xd0);

#if defined(_WIN32)
    
    emit_alu64_imm32(state, 0x81, 0, RSP, 5 * sizeof(uint64_t));
#endif
}

static inline void
emit_jmp(struct jit_state* state, uint32_t target_pc)
{
    emit1(state, 0xe9);
    emit_jump_offset(state, target_pc);
}

#endif 
