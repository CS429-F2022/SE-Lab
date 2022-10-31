#include <stdint.h>
#include <assert.h>
#include "B_COND.h"
#include "machine.h"
#include "reg.h"
#include "instr.h"
#include "err_handler.h"
#include "pipe/forward.h"

extern machine_t guest;

void decode_B_COND(instr_t * const insn) {
    int64_t imm19 = GETBF(insn->insnbits, 5, 19);
    cond_t cond = GETBF(insn->insnbits, 0, 4);
    insn->src1 = &(guest.proc->PC);
    insn->imm = imm19 << 2;
    insn->opnd1.xval = forward_reg(insn->src1);
    insn->opnd2.xval = insn->imm;
    insn->cond = cond;
    insn->cc.ccval = guest.proc->NZCV.bits->ccval;
}

static bool _B_COND_holds(instr_t * const insn) {
    switch (insn->cond) {
        case C_EQ: return (GET_ZF(insn->cc.ccval) == 1);
        case C_NE: return !(GET_ZF(insn->cc.ccval) == 1);
        case C_CS: return (GET_CF(insn->cc.ccval) == 1);
        case C_CC: return !(GET_CF(insn->cc.ccval) == 1);
        case C_MI: return (GET_NF(insn->cc.ccval) == 1);
        case C_PL: return !(GET_NF(insn->cc.ccval) == 1);
        case C_VS: return (GET_VF(insn->cc.ccval) == 1);
        case C_VC: return !(GET_VF(insn->cc.ccval) == 1);
        case C_HI: return (GET_CF(insn->cc.ccval) == 1 && GET_ZF(insn->cc.ccval) == 0);
        case C_LS: return !(GET_CF(insn->cc.ccval) == 1 && GET_ZF(insn->cc.ccval) == 0);
        case C_GE: return (GET_NF(insn->cc.ccval) == GET_VF(insn->cc.ccval));
        case C_LT: return !(GET_NF(insn->cc.ccval) == GET_VF(insn->cc.ccval));
        case C_GT: return (GET_NF(insn->cc.ccval) == GET_VF(insn->cc.ccval) && GET_ZF(insn->cc.ccval) == 0);
        case C_LE:return ! (GET_NF(insn->cc.ccval) == GET_VF(insn->cc.ccval) && GET_ZF(insn->cc.ccval) == 0);
        case C_AL: case C_NV: return true;
        case C_ERROR: IMPOSSIBLE(); break;
    }
    return false;
}

void execute_B_COND(instr_t * const insn) {
    insn->val_ex.xval = insn->opnd1.xval + insn->opnd2.xval;
    insn->branch_PC = insn->val_ex.xval;
    insn->cond_holds = _B_COND_holds(insn);
}
