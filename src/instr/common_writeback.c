#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "err_handler.h"
#include "instr.h"
#include "machine.h"

void common_writeback_alu_X(instr_t * const insn) {
    insn->dst->bits->xval = insn->val_ex.xval;
    return;
}

void common_writeback_alu_W(instr_t * const insn) {
    insn->dst->bits->wval = insn->val_ex.wval;
    return;
}

void common_writeback_mem_X(instr_t * const insn) {
    insn->dst->bits->xval = insn->val_mem.xval;
    return;
}

void common_writeback_mem_W(instr_t * const insn) {
    insn->dst->bits->wval = insn->val_mem.wval;
    return;
}

void common_writeback_special(instr_t * const insn) {
    assert(insn->op == OP_BL);
    insn->dst->bits->xval = insn->next_PC; // Return address from call.
    return;
}

void common_writeback_none(instr_t * const insn) {
    return;
}