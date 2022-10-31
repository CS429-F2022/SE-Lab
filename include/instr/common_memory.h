#ifndef _COMMON_MEMORY_H_
#define _COMMON_MEMORY_H_
#include "../instr.h"

void common_memory_load_LX(instr_t * const);
void common_memory_load_BW(instr_t * const);
void common_memory_store_XL(instr_t * const);
void common_memory_store_WB(instr_t * const);
void common_memory_none(instr_t * const);
#endif