#ifndef _COMMON_WRITEBACK_H_
#define _COMMON_WRITEBACK_H_
#include "../instr.h"

void common_writeback_alu_X(instr_t * const);
void common_writeback_alu_W(instr_t * const);
void common_writeback_mem_X(instr_t * const);
void common_writeback_mem_W(instr_t * const);
void common_writeback_special(instr_t * const);
void common_writeback_none(instr_t * const);
#endif