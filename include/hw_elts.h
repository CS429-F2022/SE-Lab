#ifndef _HW_ELTS_H_
#define _HW_ELTS_H_
#include <stdint.h>
#include <stdbool.h>
#include "instr.h"

extern comb_logic_t imem(uint64_t imem_addr,                                                    // in, data
                         uint32_t *imem_rval, bool *imem_err);                                  // out
extern comb_logic_t regfile(uint8_t src1, uint8_t src2, uint8_t dst, uint64_t val_w,            // in, data
                            bool src1_31isSP, bool src2_31isSP, bool dst_31isSP, bool w_enable, // in, control
                            uint64_t *val_a, uint64_t *val_b);                                  // out
extern comb_logic_t alu(uint64_t alu_vala, uint64_t alu_valb, uint8_t alu_valhw,               // in, data
                        alu_op_t ALUop, bool set_CC, cond_t cond,                               // in, control
                        uint64_t *val_e, bool *cond_val);                                       // out
extern comb_logic_t dmem(uint64_t dmem_addr, uint64_t dmem_wval,                                // in, data
                         bool dmem_read, bool dmem_write,                                       // in, control
                         uint64_t *dmem_rval, bool *dmem_err);                                   // out
#endif