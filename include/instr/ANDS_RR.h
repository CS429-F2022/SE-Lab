#ifndef _ANDS_RR_H_
#define _ANDS_RR_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_ANDS_RR(instr_t * const);
extern void execute_ANDS_RR(instr_t * const);
#endif