#include <assert.h>
#include "HLT.h"
#include "machine.h"

extern machine_t guest;

void decode_HLT(instr_t * const insn) {
    assert(insn->insnbits == 0xd4400000);
    return;
}

void execute_HLT(instr_t * const insn) { // Fix.
    return;
}