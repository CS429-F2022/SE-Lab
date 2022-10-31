#ifndef _EOR_RR_H_
#define _EOR_RR_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_EOR_RR(instr_t * const);
extern void execute_EOR_RR(instr_t * const);
#endif