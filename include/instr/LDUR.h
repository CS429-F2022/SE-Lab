#ifndef _LDUR_H_
#define _LDUR_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_LDUR(instr_t * const);
extern void execute_LDUR(instr_t * const);
#endif