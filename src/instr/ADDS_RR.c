#include <stdint.h>
#include "ADDS_RR.h"
#include "machine.h"
#include "reg.h"
#include "instr.h"
#include "pipe/forward.h"

extern machine_t guest;

void decode_ADDS_RR(instr_t * const insn) {
    unsigned d = GETBF(insn->insnbits, 0, 5);
    unsigned n = GETBF(insn->insnbits, 5, 5);
    unsigned m = GETBF(insn->insnbits, 16, 5);
    insn->src1 = &(guest.proc->GPR.names64[n]);
    insn->src2 = &(guest.proc->GPR.names64[m]);
    insn->dst = &(guest.proc->GPR.names64[d]);
    insn->opnd1.xval = forward_reg(insn->src1);
    insn->opnd2.xval = forward_reg(insn->src2);
}

void execute_ADDS_RR(instr_t * const insn) {
    __int128_t usum = ((uint64_t) insn->opnd1.xval) + ((uint64_t) insn->opnd2.xval);
    __int128_t ssum = insn->opnd1.xval + insn->opnd2.xval;
    int64_t result = (int64_t) usum;
    insn->val_ex.xval = result;
    insn->cc.ccval =  PACK_CC((result >> 63) & 0x1U, 
                              result == 0,
                              ((uint64_t) result) == usum ? 0 : 1,
                              ((int64_t) result) == ssum ? 0 : 1
                             );
    guest.proc->NZCV.bits->ccval = insn->cc.ccval; // NZCV is updated in X. Only GPRs are updated in W.
}
