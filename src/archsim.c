/**************************************************************************
 * STUDENTS: DO NOT MODIFY.
 * 
 * C S 429 architecture emulator
 * 
 * archsim.c - The top-level loop of the emulator.
 * 
 * Copyright (c) 2022. S. Chatterjee. All rights reserved.
 * May not be used, modified, or copied without permission.
 **************************************************************************/ 

#include "archsim.h"

machine_t guest;
opcode_t itable[2<<11];
FILE *infile, *outfile, *errfile;
char *infile_name;
char *ae_prompt;
int debug_level;
uint64_t inflight_cycles;
uint64_t inflight_addr;
bool inflight;
mem_status_t dmem_status;

int main(int argc, char* argv[]) {
    debug_level = 0;
    handle_args(argc, argv);
    init();
    
    uint64_t entry = loadElf(infile_name);
    int ret = runElf(entry);
    
    finalize();
    
    return ret;
}
