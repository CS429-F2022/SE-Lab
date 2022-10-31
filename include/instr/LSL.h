#ifndef _LSL_H_
#define _LSL_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_LSL(instr_t * const);
extern void execute_LSL(instr_t * const);
#endif