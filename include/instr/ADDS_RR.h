#ifndef _ADDS_RR_H_
#define _ADDS_RR_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_ADDS_RR(instr_t * const);
extern void execute_ADDS_RR(instr_t * const);
#endif