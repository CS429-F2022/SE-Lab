#include <assert.h>
#include <stdlib.h>
#include "err_handler.h"
#include "STURB.h"
#include "machine.h"
#include "pipe/forward.h"

extern machine_t guest;

void decode_STURB(instr_t * const insn) {
    int32_t instr = insn->insnbits;
    unsigned opcode = GETBF(instr, 21, 11);
    assert(0x1C0U == opcode);

    int imm9 = GETBF(instr, 12, 9);
    int64_t offset = imm9; // Check
    int n = GETBF(instr, 0, 5);
    insn->op = OP_STURB;
    insn->src1 = n == 31 ? &(guest.proc->SP) : guest.proc->GPR.names64 + n;
    insn->imm = offset;
    insn->opnd1.xval = forward_reg(insn->src1);
    insn->opnd2.xval = insn->imm;
    if (31 == n) {
        if (0 != insn->opnd1.xval) {
            logging(LOG_FATAL, "Stack pointer misaligned");
            exit(EXIT_FAILURE);
        }
    }
    return;
}

void execute_STURB(instr_t * const insn) {
    insn->val_ex.xval = insn->opnd1.xval + insn->opnd2.xval;
    return;
}
