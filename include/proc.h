#ifndef _PROC_H_
#define _PROC_H_
#include <stdint.h>
#include "reg.h"
#include "instr.h"

// Processor state.
typedef struct proc {
    reg_file_t GPR;
    // reg_file_t FPR;
    reg_t PC;
    reg_t SP;
    reg_t NZCV;

    pipe_reg_t *f_insn;
    pipe_reg_t *d_insn;
    pipe_reg_t *x_insn;
    pipe_reg_t *m_insn;
    pipe_reg_t *w_insn;
} proc_t;

extern int runElf(const uint64_t);
#endif