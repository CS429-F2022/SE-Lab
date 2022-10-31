/**************************************************************************
 * C S 429 architecture emulator
 * 
 * instr/common_pc_update.h - Header file for routines for updating PC.
 * 
 * Copyright (c) 2022. S. Chatterjee. All rights reserved.
 * May not be used, modified, or copied without permission.
 **************************************************************************/ 

#ifndef _COMMON_UPDATE_PC_H_
#define _COMMON_UPDATE_PC_H_
#include "../instr.h"

extern void update_pc_next(instr_t * const);
extern void update_pc_branch(instr_t * const);
extern void update_pc_halt(instr_t * const);

#endif