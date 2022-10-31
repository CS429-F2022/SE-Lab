#include <stdlib.h>
#include <stdint.h>
#include "MOVK.h"
#include "machine.h"
#include "reg.h"
#include "instr.h"
#include "err_handler.h"
#include "pipe/forward.h"

extern machine_t guest;

void decode_MOVK(instr_t * const insn) {
    unsigned d = GETBF(insn->insnbits, 0, 5);
    unsigned imm16 = GETBF(insn->insnbits, 5, 16);
    uint8_t hw = GETBF(insn->insnbits, 21, 2);
    insn->src1 = &(guest.proc->GPR.names64[d]);
    insn->imm = imm16;
    uint8_t pos = hw << 4;
    insn->dst = &(guest.proc->GPR.names64[d]);
    insn->opnd1.xval = forward_reg(insn->src1);
    insn->opnd2.xval = insn->imm << pos;
    insn->shift = pos;
}

void execute_MOVK(instr_t * const insn) {
    int64_t mask = ((1UL << 16) - 1) << (insn->shift);
    insn->val_ex.xval = (insn->opnd1.xval & ~mask) | (insn->opnd2.xval & mask);
}
