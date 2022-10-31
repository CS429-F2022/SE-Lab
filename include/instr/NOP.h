#ifndef _NOP_H_
#define _NOP_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_NOP(instr_t * const);
extern void execute_NOP(instr_t * const);
#endif