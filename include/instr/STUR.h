#ifndef _STUR_H_
#define _STUR_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_STUR(instr_t * const);
extern void execute_STUR(instr_t * const);
#endif