#ifndef _ADD_RI_H_
#define _ADD_RI_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_ADD_RI(instr_t * const);
extern void execute_ADD_RI(instr_t * const);
#endif