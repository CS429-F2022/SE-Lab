#include "machine.h"

extern machine_t guest;
extern instr_t *bubble_instr;

/* Bubble and stall checking logic.
 * STUDENT TO-DO:
 * Implement logic for hazard handling.
 * The three functions are optional helper 
 * functions, but you MUST implement
 * handle_hazards.
 * You may use any stage of the pipeline.
 */

bool check_ret_hazard() {
    return false;
}

bool check_mispred_branch_hazard() {
    return false;
}

bool check_load_use_hazard() {
    return false;
}

void handle_hazards() {
    return;
}