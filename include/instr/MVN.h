#ifndef _MVN_H_
#define _MVN_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_MVN(instr_t * const);
extern void execute_MVN(instr_t * const);
#endif