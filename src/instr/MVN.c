#include <stdint.h>
#include "MVN.h"
#include "machine.h"
#include "reg.h"
#include "instr.h"
#include "pipe/forward.h"

extern machine_t guest;

void decode_MVN(instr_t * const insn) {
    unsigned d = GETBF(insn->insnbits, 0, 5);
    unsigned m = GETBF(insn->insnbits, 16, 5);
    insn->src1 = &(guest.proc->GPR.names64[m]);
    insn->dst = &(guest.proc->GPR.names64[d]);
    insn->opnd1.xval = forward_reg(insn->src1);
}

void execute_MVN(instr_t * const insn) {
    insn->val_ex.xval = ~(insn->opnd1.xval);
}
