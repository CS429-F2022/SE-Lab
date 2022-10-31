/**************************************************************************
 * STUDENTS: DO NOT MODIFY.
 * 
 * C S 429 architecture emulator
 * 
 * machine.c - Module for initializing the guest machine.
 * 
 * Copyright (c) 2022. S. Chatterjee. All rights reserved.
 * May not be used, modified, or copied without permission.
 **************************************************************************/ 

#include <stdlib.h>
#include <string.h>
#include "machine.h"

/* Created from command-line arguments */
#ifdef CACHE
extern int s, b, E, d;
extern uint64_t inflight_cycles;
extern uint64_t inflight_addr;
extern bool inflight;
extern mem_status_t dmem_status;
#endif

static uint64_t seg_starts[] = {
    0x0ULL,
    0x400000ULL,
    0x800000ULL,
    0x10000000ULL,
    0x400000000ULL,
    0x800000000ULL,
    0x1000000000000ULL
};

static uint8_t seg_prots[] = {0x0, 0x5, 0x6, 0x6, 0x5, 0x6, 0x0};

extern machine_t guest;

#define NUM_ADDR_BITS 64

void init_machine(char *name, unsigned word_size, byte_order_t code_order, byte_order_t data_order) {
    guest.name = malloc(strlen(name)+1);
    strcpy(guest.name, name);
    guest.word_size = word_size;
    guest.code_order = code_order;
    guest.data_order = data_order;
    guest.mode = MODE_KER;

    guest.proc = malloc(sizeof(proc_t));
    init_reg_file(&(guest.proc->GPR), "GPR", 31, 64);
    // init_reg_file(&(guest.proc->FPR), "FPR", 32, 128);
    init_reg(&(guest.proc->PC), "PC", -1, WVAR_64, (gpregval_t *) malloc(sizeof(gpregval_t)));
    init_reg(&(guest.proc->SP), "SP", -1, WVAR_64, (gpregval_t *) malloc(sizeof(gpregval_t)));
    init_reg(&(guest.proc->NZCV), "NZCV", -1, WVAR_4, (gpregval_t *) malloc(sizeof(gpregval_t)));
    
    guest.mem = malloc(sizeof(mem_t));
    guest.mem->max_addr = UINT_FAST64_MAX;
    guest.mem->addr_size = NUM_ADDR_BITS;
    guest.mem->gran = BYTE_GRAN;
    for (int i = 0; i <= KERNEL_SEG; i++) {
        guest.mem->seg_start_addr[i] = seg_starts[i];
        guest.mem->seg_prot[i] = seg_prots[i];
    }

#ifdef CACHE
    guest.cache = create_cache(s, b, E, d);
    inflight_cycles = guest.cache->d;
    inflight_addr = 0;
    inflight = false;
    dmem_status = READY;
#endif
}