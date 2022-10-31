#include <stdlib.h>
#include <stdint.h>
#include "STUR.h"
#include "machine.h"
#include "reg.h"
#include "instr.h"
#include "err_handler.h"
#include "pipe/forward.h"

extern machine_t guest;

void decode_STUR(instr_t * const insn) {
    unsigned t = GETBF(insn->insnbits, 0, 5);
    unsigned n = GETBF(insn->insnbits, 5, 5);
    int64_t offset = GETBF(insn->insnbits, 12, 9);
    if (n == 31) {
        if (0 != guest.proc->SP.bits->xval % 8) {
            logging(LOG_FATAL, "SP unaligned on 8-byte boundary");
            exit(EXIT_FAILURE);
        }
        insn->src1 = &(guest.proc->SP);
    }
    else
        insn->src1 = &(guest.proc->GPR.names64[n]);
    insn->imm = offset;
    insn->src2 = &(guest.proc->GPR.names64[t]);
    insn->opnd1.xval = forward_reg(insn->src1);
    insn->opnd2.xval = forward_reg(insn->src2);
}

void execute_STUR(instr_t * const insn) {
    insn->val_ex.xval = insn->opnd1.xval + insn->imm;
    insn->val_mem.xval = insn->opnd2.xval;
}
