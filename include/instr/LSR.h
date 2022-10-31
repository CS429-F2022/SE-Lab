#ifndef _LSR_H_
#define _LSR_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_LSR(instr_t * const);
extern void execute_LSR(instr_t * const);
#endif