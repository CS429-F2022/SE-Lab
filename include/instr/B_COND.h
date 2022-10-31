#ifndef _B_COND_H_
#define _B_COND_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_B_COND(instr_t * const);
extern void execute_B_COND(instr_t * const);
#endif