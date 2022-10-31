#include <stdint.h>
#include "ASR.h"
#include "machine.h"
#include "reg.h"
#include "instr.h"
#include "pipe/forward.h"

extern machine_t guest;

void decode_ASR(instr_t * const insn) {
    unsigned d = GETBF(insn->insnbits, 0, 5);
    unsigned n = GETBF(insn->insnbits, 5, 5);
    unsigned R = GETBF(insn->insnbits, 16, 6);
    insn->src1 = &(guest.proc->GPR.names64[n]);
    insn->imm = R;
    insn->dst = &(guest.proc->GPR.names64[d]);
    insn->opnd1.xval = forward_reg(insn->src1);
    insn->opnd2.xval = R;
}

void execute_ASR(instr_t * const insn) {
    insn->val_ex.xval = insn->opnd1.xval >> insn->opnd2.xval;
    // TODO: Verify that the implementation actually performs an arithmetic right shift.
}
