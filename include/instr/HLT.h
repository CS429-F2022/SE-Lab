#ifndef _HLT_H_
#define _HLT_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_HLT(instr_t * const);
extern void execute_HLT(instr_t * const);
#endif