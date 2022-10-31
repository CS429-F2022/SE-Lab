#ifndef _MOVK_H_
#define _MOVK_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_MOVK(instr_t * const);
extern void execute_MOVK(instr_t * const);
#endif