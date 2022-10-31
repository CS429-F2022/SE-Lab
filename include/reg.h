#ifndef _REG_H_
#define _REG_H_

#include <stdint.h>

typedef enum wvar {
    WVAR_4,
    WVAR_32,
    WVAR_64,
    WVAR_ERROR = -1
} wvar_t;

typedef union gpregval {
    uint8_t ccval; // This is to be used only for condition codes, i.e., for the NZCV register.
    int8_t  sval;
    int32_t wval;
    int64_t xval;
} gpregval_t, val_t;// TODO: Check dependence on endian-ness.

// A single register.
typedef struct reg {
    char        *name;  // The name of the register.
    unsigned    index;  // An index into a register file.
    wvar_t      width;  // Bit width of the register.
    gpregval_t  *bits;   // A pointer to the bit storage.
} reg_t;

// Register file.
typedef struct reg_file {
    char        *name;  // Name of the register file.
    unsigned    num;    // How many registers in the file.
    unsigned    width;  // How wide is each register?
    gpregval_t  *bits;  // Storage area for the bits. Allocate an array of "num" gpregval_t structs.
    reg_t       *names32;
    reg_t       *names64;
} reg_file_t;

extern char *reg_prefix[];

extern void init_reg(reg_t *r, char *name, unsigned index, wvar_t width, gpregval_t *bits);
extern void init_reg_file(reg_file_t *rf, char *name, unsigned num, unsigned width);
#endif