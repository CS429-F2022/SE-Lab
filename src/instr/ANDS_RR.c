#include <stdint.h>
#include "ANDS_RR.h"
#include "machine.h"
#include "reg.h"
#include "instr.h"
#include "pipe/forward.h"

extern machine_t guest;

void decode_ANDS_RR(instr_t * const insn) {
    unsigned d = GETBF(insn->insnbits, 0, 5);
    unsigned n = GETBF(insn->insnbits, 5, 5);
    unsigned m = GETBF(insn->insnbits, 16, 5);
    insn->src1 = &(guest.proc->GPR.names64[n]);
    insn->src2 = &(guest.proc->GPR.names64[m]);
    insn->dst = &(guest.proc->GPR.names64[d]);
    insn->opnd1.xval = forward_reg(insn->src1);
    insn->opnd2.xval = forward_reg(insn->src2);
}

void execute_ANDS_RR(instr_t * const insn) {
    int64_t result = insn->opnd1.xval & insn->opnd2.xval;
    insn->val_ex.xval = result;
    insn->cc.ccval =  PACK_CC((result >> 63) & 0x1U, 
                              result == 0,
                              0,
                              0
                             );
    guest.proc->NZCV.bits->ccval = insn->cc.ccval; // NZCV is updated in X. Only GPRs are updated in W.
}
