/*
 * Copyright 2015 Big Switch Networks, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http:
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef UBPF_H
#define UBPF_H

#include "ubpf_config.h"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


#if !defined(UBPF_MAX_INSTS)
#define UBPF_MAX_INSTS 65536
#endif

#if !defined(UBPF_STACK_SIZE)
#define UBPF_STACK_SIZE 512
#endif

struct ubpf_vm;
typedef uint64_t (*ubpf_jit_fn)(void *mem, size_t mem_len);

struct ubpf_vm *ubpf_create(void);
void ubpf_destroy(struct ubpf_vm *vm);


bool ubpf_toggle_bounds_check(struct ubpf_vm *vm, bool enable);



void ubpf_set_error_print(struct ubpf_vm *vm, int (*error_printf)(FILE* stream, const char* format, ...));


int ubpf_register(struct ubpf_vm *vm, unsigned int idx, const char *name, void *fn);


int ubpf_load(struct ubpf_vm *vm, const void *code, uint32_t code_len, char **errmsg);


void ubpf_unload_code(struct ubpf_vm *vm);



#if defined(UBPF_HAS_ELF_H)
int ubpf_load_elf(struct ubpf_vm *vm, const void *elf, size_t elf_len, char **errmsg);
#endif

int ubpf_exec(const struct ubpf_vm *vm, void *mem, size_t mem_len, uint64_t* bpf_return_value);

ubpf_jit_fn ubpf_compile(struct ubpf_vm *vm, char **errmsg);


int ubpf_translate(struct ubpf_vm *vm, uint8_t *buffer, size_t *size, char **errmsg);


int ubpf_set_unwind_function_index(struct ubpf_vm *vm, unsigned int idx);

void ubpf_set_registers(struct ubpf_vm *vm, uint64_t *regs);
uint64_t *ubpf_get_registers(const struct ubpf_vm *vm);

#endif
