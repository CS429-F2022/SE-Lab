#include <stdint.h>
#include <assert.h>
#include "UBFM.h"
#include "machine.h"
#include "reg.h"
#include "instr.h"
#include "err_handler.h"
#include "pipe/forward.h"

extern machine_t guest;

void decode_UBFM(instr_t * const insn) {
    unsigned d = GETBF(insn->insnbits, 0, 5);
    unsigned n = GETBF(insn->insnbits, 5, 5);
    uint8_t imms = GETBF(insn->insnbits, 10, 6);
    uint8_t immr = GETBF(insn->insnbits, 16, 6);

    insn->src1 = &(guest.proc->GPR.names64[n]);
    insn->dst = &(guest.proc->GPR.names64[d]);
    insn->opnd1.xval = forward_reg(insn->src1);
    insn->imm = immr;
    insn->opnd2.xval = insn->imm;
    // Not implementing the full functionality of UBFM, since we need only two special cases.
    // Just changing the insn->op field so that the appropriate special cases will be called in execute.
    if (0x3FU == (imms & 0x3FU)) insn->op = OP_LSR;
    else {
        if (imms+1 == immr) insn->op = OP_LSL;
        else IMPOSSIBLE();
    }
}

void execute_UBFM(instr_t * const insn) {
    // This routine should never even be called, because of the hackery with insn->op in decode_UBFM.
    return;
}
