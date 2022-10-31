#include <stdint.h>
#include "RET.h"
#include "machine.h"
#include "reg.h"
#include "instr.h"
#include "pipe/forward.h"

extern machine_t guest;

void decode_RET(instr_t * const insn) {
    unsigned n = GETBF(insn->insnbits, 5, 5);
    insn->src1 = &(guest.proc->GPR.names64[n]);
    insn->opnd1.xval = forward_reg(insn->src1);
}

void execute_RET(instr_t * const insn) {
    insn->branch_PC = insn->opnd1.xval;
    return;
}
