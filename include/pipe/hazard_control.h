
#include <stdint.h>

bool check_ret_hazard();
bool check_mispred_branch_hazard();
bool check_load_use_hazard();
void handle_hazards();