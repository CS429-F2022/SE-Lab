#ifndef _BL_H_
#define _BL_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_BL(instr_t * const);
extern void execute_BL(instr_t * const);
#endif