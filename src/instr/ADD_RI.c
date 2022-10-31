#include <assert.h>
#include "ADD_RI.h"
#include "machine.h"
#include "pipe/forward.h"

extern machine_t guest;

void decode_ADD_RI(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    assert(EXTRACT(instr, 0xFF800000, 23) == 0x122U);

    uint8_t d = EXTRACT(instr, 0x1FU, 0);
    uint8_t n = EXTRACT(instr, 0x3E0U, 5);
    uint16_t imm12 = EXTRACT(instr, 0x3FFC00U, 10);
    uint8_t sh = EXTRACT(instr, 400000U, 22);
    // bool is_aliased = (sh == 0 && imm12 == 0 && (d == 31 || n == 31));

    // insn->op = is_aliased ? OP_MOV : OP_ADD;
    insn->dst = (d == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names64 + d);
    insn->src1 = (n == 31) ? &(guest.proc->SP) : (guest.proc->GPR.names64 + n);
    insn->imm = sh ? imm12 << 12 : imm12;
    insn->opnd1.xval = forward_reg(insn->src1);
    insn->opnd2.xval = insn->imm;
    return;
}

void execute_ADD_RI(instr_t * const insn) {
    insn->val_ex.xval = insn->opnd1.xval + insn->opnd2.xval;
    return;
}
