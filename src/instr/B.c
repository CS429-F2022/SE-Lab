#include <stdint.h>
#include "B.h"
#include "machine.h"
#include "reg.h"
#include "instr.h"
#include "pipe/forward.h"

extern machine_t guest;

void decode_B(instr_t * const insn) {
    int64_t imm26 = GETBF(insn->insnbits, 0, 26);
    insn->src1 = &(guest.proc->PC);
    insn->imm = imm26 << 2;
    insn->opnd1.xval = forward_reg(insn->src1);
    insn->opnd2.xval = insn->imm;
}

void execute_B(instr_t * const insn) {
    insn->val_ex.xval = insn->opnd1.xval + insn->opnd2.xval;
    insn->branch_PC = insn->val_ex.xval;
}
