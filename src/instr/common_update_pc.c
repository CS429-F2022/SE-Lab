/**************************************************************************
 * C S 429 architecture emulator
 * 
 * instr/common_pc_update.c - Routines for updating PC.
 * 
 * Copyright (c) 2022. S. Chatterjee. All rights reserved.
 * May not be used, modified, or copied without permission.
 **************************************************************************/ 

#include <assert.h>
#include <stdlib.h>
#include "machine.h"
#include "instr.h"

extern machine_t guest;

/* 
 * Update PC action for those instructions that continue to their successor.
 *
 * Do not re-write.
 */
void update_pc_next(instr_t * const insn) {
    guest.proc->PC.bits->xval = insn->next_PC;
    return;
}

/* 
 * Update PC action for those instructions that continue to their target.
 *
 * Do not re-write.
 */
void update_pc_branch(instr_t * const insn) {
    guest.proc->PC.bits->xval = insn->branch_PC;
    return;
}

/* 
 * Update PC action for HLT.
 *
 * Do not re-write.
 */
void update_pc_halt(instr_t * const insn) {
    exit(EXIT_FAILURE);
    return; // Not reached.
}

