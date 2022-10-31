#ifndef _LDURB_H_
#define _LDURB_H_
#include <stdint.h>
#include "../instr.h"

extern void decode_LDURB(instr_t * const);
extern void execute_LDURB(instr_t * const);
#endif