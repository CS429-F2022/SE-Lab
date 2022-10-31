#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "err_handler.h"
#include "instr.h"
#include "machine.h"

void common_memory_load_LX(instr_t * const insn) {
    insn->val_mem.xval = mem_read_L(insn->val_ex.xval);
    return;
}

void common_memory_load_BW(instr_t * const insn) {
    insn->val_mem.wval = (uint32_t) mem_read_B(insn->val_ex.xval);
    return;
}

void common_memory_store_XL(instr_t * const insn) {
    mrc_t ret = mem_write_L(insn->val_ex.xval, insn->val_mem.xval);
    assert(WRITE_SUCCESS == ret);
    return;
}

void common_memory_store_WB(instr_t * const insn) {
    mrc_t ret = mem_write_B(insn->val_ex.wval, insn->opnd2.xval);
    assert(WRITE_SUCCESS == ret);
    return;
}

void common_memory_none(instr_t * const insn) {
    return;
}