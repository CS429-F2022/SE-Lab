#ifndef _UBFM_H_
#define _UBFM_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_UBFM(instr_t * const);
extern void execute_UBFM(instr_t * const);
#endif