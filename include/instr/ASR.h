#ifndef _ASR_H_
#define _ASR_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_ASR(instr_t * const);
extern void execute_ASR(instr_t * const);
#endif