#ifndef _MOVZ_H_
#define _MOVZ_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_MOVZ(instr_t * const);
extern void execute_MOVZ(instr_t * const);
#endif