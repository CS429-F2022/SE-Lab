#ifndef _RET_H_
#define _RET_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_RET(instr_t * const);
extern void execute_RET(instr_t * const);
#endif