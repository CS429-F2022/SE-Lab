/**************************************************************************
 * STUDENTS: DO NOT MODIFY.
 * 
 * C S 429 architecture emulator
 * 
 * mem.c - Module for memory operations.
 * 
 * Copyright (c) 2022. S. Chatterjee. All rights reserved.
 * May not be used, modified, or copied without permission.
 **************************************************************************/ 

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "err_handler.h"
#include "mem.h"
#include "ptable.h"
#include "machine.h"

extern machine_t guest;

#ifdef CACHE
extern uint64_t inflight_cycles;
extern uint64_t inflight_addr;
extern bool inflight;
extern mem_status_t dmem_status;
#endif

const uint64_t NULL_ADDR = 0x0UL;
const uint64_t IO_CHAR_ADDR = 0xFFFFFFFFFFFFFFFFUL;
const uint64_t RET_FROM_MAIN_ADDR = 0xFFFFFFFFFFFFFFFFUL-4;


static bool is_special_addr(const uint64_t addr) {
    return ((NULL_ADDR == addr) || 
            (IO_CHAR_ADDR == addr) || 
            (RET_FROM_MAIN_ADDR == addr));
}

static byte_order_t get_byte_order(const uint64_t addr) {
    if ((guest.mem->seg_start_addr[TEXT_SEG] <= addr) && 
        (addr < guest.mem->seg_start_addr[DATA_SEG]))
        return guest.code_order;
    return guest.data_order;
}

static uint8_t get_prot_bits(const uint64_t addr) {
    for (int i = 0; i < KERNEL_SEG; i++) {
        if ((guest.mem->seg_start_addr[i] <= addr) && 
            (addr < guest.mem->seg_start_addr[i+1]))
            return guest.mem->seg_prot[i];
    }
    return guest.mem->seg_prot[KERNEL_SEG];
}

static uint8_t _mem_read_byte(const uint64_t addr) {
    uint64_t pnum = addr / PAGESIZE;
    uint64_t poff = addr % PAGESIZE;
    pte_ptr_t page = get_page(pnum);
    if (NULL == page)
        page = add_page(pnum, get_prot_bits(addr));
    return page->p_data[poff];
}

static uint64_t _mem_read_LE(const uint64_t addr, const unsigned width) {
    uint64_t retval = 0ULL;
    for (int i = width-1; i >= 0; i--)
        retval = (retval << 8) + _mem_read_byte(addr+i);
    return retval;
}

static uint64_t _mem_read_BE(const uint64_t addr, const unsigned width) {
    uint64_t retval = 0ULL;
    for (int i = 0; i < width; i++)
        retval = (retval << 8) + _mem_read_byte(addr+i);
    return retval;
}

static uint64_t _mem_read_special(const uint64_t addr, const unsigned width) {
    if (NULL_ADDR == addr) {
        logging(LOG_FATAL, "Null pointer read attempt");
        exit(EXIT_FAILURE);
    }
    if (IO_CHAR_ADDR == addr) {
        uint8_t data8;
        uint16_t data16;
        uint32_t data32;
        uint64_t data64;
        switch (width) {
            case 1: scanf("%c\n", &data8); return (char) (data8&0xFFU); break;
            case 2: scanf("%hd\n", &data16); return (short) (data16 & 0xFFFFU); break;
            case 4: scanf("%d\n", &data32); return (int) (data32 & 0xFFFFFFFFU); break;
            case 8: scanf("%ld\n", &data64); return (long) data64; break;
            default: assert(false); break;
        }
    }
    if (RET_FROM_MAIN_ADDR == addr) {return 0;}
    assert(false); return 0;
}

uint64_t _mem_read(const uint64_t addr, const unsigned width) {
    if (is_special_addr(addr))
        return _mem_read_special(addr, width);

    byte_order_t b = get_byte_order(addr);
    switch (b) {
        case L_ENDIAN:
            return _mem_read_LE(addr, width);
        case B_ENDIAN:
            return _mem_read_BE(addr, width);
        default:
            assert(false); return 0;
    }
}

static write_ret_code_t _mem_write_byte(const uint64_t addr, const uint8_t data) {
    uint64_t pnum = addr / PAGESIZE;
    uint64_t poff = addr % PAGESIZE;
    pte_ptr_t page = get_page(pnum);
    if (NULL == page) {
        page = add_page(pnum, 7);//FIX.
    }
    page->p_data[poff] = data;
    //printf("%lx:%lx: %x\n", pnum, poff, data);
    return WRITE_SUCCESS;
}

static write_ret_code_t _mem_write_LE(const uint64_t addr, const uint64_t data, const unsigned width) {
    uint8_t *s = (uint8_t *) &data;
    write_ret_code_t retval = WRITE_FAILURE;
    for (int i = 0; i < width; i++)
        retval |= _mem_write_byte(addr+i, s[i]);
    return retval;
}

static write_ret_code_t _mem_write_BE(const uint64_t addr, const uint64_t data, const unsigned width) {
    uint8_t *s = (uint8_t *) &data;
    write_ret_code_t retval = WRITE_FAILURE;
    for (int i = 0; i < width; i++)
        retval |= _mem_write_byte(addr+i, s[width-i-1]);
    return retval;
}

static write_ret_code_t _mem_write_special(const uint64_t addr, const uint64_t data, const unsigned width) {
    if (NULL_ADDR == addr) {
        logging(LOG_INFO, "Null pointer write attempt");
        return WRITE_SUCCESS;
    }
    if (IO_CHAR_ADDR == addr) {
        switch (width) {
            case 1: putchar(data & 0xFFU); break;
            case 2: printf("%hd %0#4hx\n", (short) (data & 0xFFFFU), (short) (data & 0xFFFFU)); break;
            case 4: printf("%d %0#8x\n", (int) (data & 0xFFFFFFFFU), (int) (data & 0xFFFFFFFFU)); break;
            case 8: 
                printf("%ld %0#16lx\n", (long) data, (long) data);
                char printbuf[100];
                sprintf(printbuf, "%ld %0#16lx", (long) data, (long) data);
                logging(LOG_OUTPUT, printbuf);
                break;
            default: assert(false); break;
        }
        return WRITE_SUCCESS;    
    }
    assert(false); return WRITE_SUCCESS;
}

write_ret_code_t _mem_write(const uint64_t addr, const uint64_t data, const unsigned width) {
    if (is_special_addr(addr))
        return _mem_write_special(addr, data, width);

    byte_order_t b = get_byte_order(addr);
    switch (b) {
        case L_ENDIAN:
            return _mem_write_LE(addr, data, width);
        case B_ENDIAN:
            return _mem_write_BE(addr, data, width);
        default:
            return WRITE_FAILURE;
    }
}

#ifdef CACHE
uint64_t _mem_read_cache(const uint64_t addr, const unsigned width) {
    if (is_special_addr(addr))
        return _mem_read_special(addr, width);

    // byte_order_t b = get_byte_order(addr);

    size_t B = 1 << guest.cache->b;
	uword_t current_address = addr;
    uint64_t data = 0;

    for (size_t i = 0; i < width; i++) {
        if (!check_hit(guest.cache, current_address, READ)) {
            uword_t block_address = current_address & ~(B-1);
            if(inflight_addr != block_address || !inflight) {
                inflight_addr = block_address;
                inflight_cycles = guest.cache->d;
                inflight = true;
            }

            inflight_cycles--;
            if(inflight_cycles > 0) {
                dmem_status = IN_FLIGHT;
                return 0;
            }

            inflight = false;

            uint8_t *block = calloc(B, 1);
            for (int j = 0; j < B; j++) {
                block[j] = _mem_read_LE((addr+j) & ~(B-1), 1);
            }

            evicted_line_t *evicted = handle_miss(guest.cache, block_address, READ, block);
            data = *((uint64_t *)block + (addr & (B-1)));

            if (evicted->valid && evicted->dirty) {
                for (int j = 0; j < B; j++) {
                    _mem_write_LE((evicted->addr+j) & ~(B-1), evicted->data[j], 1);
                }
            }

            free(block);
            free(evicted->data);
            free(evicted);
        }
        current_address++;
    }
    dmem_status = READY;
    return data;
}

write_ret_code_t _mem_write_cache(const uint64_t addr, const uint64_t data, const unsigned width) {
    if (is_special_addr(addr))
        return _mem_read_special(addr, width);

    // byte_order_t b = get_byte_order(addr);

    size_t B = 1 << guest.cache->b;
	uword_t current_address = addr; 

    for (size_t i = 0; i < width; i++) {
        if (!check_hit(guest.cache, current_address, READ)) {
            uword_t block_address = current_address & ~(B-1);
            if(inflight_addr != block_address || !inflight) {
                inflight_addr = block_address;
                inflight_cycles = guest.cache->d;
                inflight = true;
            }

            inflight_cycles--;
            if(inflight_cycles > 0) {
                dmem_status = IN_FLIGHT;
                return WRITE_FAILURE;
            }

            inflight = false;

            uint8_t *block = calloc(B, 1);
            for (int j = 0; j < B; j++) {
                block[j] = _mem_read_LE(addr+j, 1);
            }

            evicted_line_t *evicted = handle_miss(guest.cache, block_address, READ, block);

            if (evicted->valid && evicted->dirty) {
                for (int j = 0; j < B; j++) {
                    _mem_write_LE(evicted->addr+j, evicted->data[j], 1);
                }
            }

            free(block);
            free(evicted->data);
            free(evicted);
        }
        current_address++;
    }
    dmem_status = READY;
    return WRITE_SUCCESS;
}

char      mem_read_B (const uint64_t addr) {return (char)      _mem_read_cache(addr, 1);}
short     mem_read_S (const uint64_t addr) {return (short)     _mem_read_cache(addr, 2);}
int       mem_read_I (const uint64_t addr) {return (int)       _mem_read(addr, 4);}
long      mem_read_L (const uint64_t addr) {return (long)      _mem_read_cache(addr, 8);}
long long mem_read_LL(const uint64_t addr) {return (long long) _mem_read_cache(addr, 8);}

write_ret_code_t mem_write_B (const uint64_t addr, const char      data) {return _mem_write_cache(addr, (uint64_t) data, 1);}
write_ret_code_t mem_write_S (const uint64_t addr, const short     data) {return _mem_write_cache(addr, (uint64_t) data, 2);}
write_ret_code_t mem_write_I (const uint64_t addr, const int       data) {return _mem_write_cache(addr, (uint64_t) data, 4);}
write_ret_code_t mem_write_L (const uint64_t addr, const long      data) {return _mem_write_cache(addr, (uint64_t) data, 8);}
write_ret_code_t mem_write_LL(const uint64_t addr, const long long data) {return _mem_write_cache(addr, (uint64_t) data, 8);}
#else

char      mem_read_B (const uint64_t addr) {return (char)      _mem_read(addr, 1);}
short     mem_read_S (const uint64_t addr) {return (short)     _mem_read(addr, 2);}
int       mem_read_I (const uint64_t addr) {return (int)       _mem_read(addr, 4);}
long      mem_read_L (const uint64_t addr) {return (long)      _mem_read(addr, 8);}
long long mem_read_LL(const uint64_t addr) {return (long long) _mem_read(addr, 8);}

write_ret_code_t mem_write_B (const uint64_t addr, const char      data) {return _mem_write(addr, (uint64_t) data, 1);}
write_ret_code_t mem_write_S (const uint64_t addr, const short     data) {return _mem_write(addr, (uint64_t) data, 2);}
write_ret_code_t mem_write_I (const uint64_t addr, const int       data) {return _mem_write(addr, (uint64_t) data, 4);}
write_ret_code_t mem_write_L (const uint64_t addr, const long      data) {return _mem_write(addr, (uint64_t) data, 8);}
write_ret_code_t mem_write_LL(const uint64_t addr, const long long data) {return _mem_write(addr, (uint64_t) data, 8);}
#endif