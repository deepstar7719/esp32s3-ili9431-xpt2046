// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// ------ //
// tft_io //
// ------ //

#define tft_io_wrap_target 11
#define tft_io_wrap 31

#define tft_io_offset_block_fill 0u
#define tft_io_offset_start_tx 11u
#define tft_io_offset_start_8 18u
#define tft_io_offset_set_addr_window 21u

static const uint16_t tft_io_program_instructions[] = {
    0x98a0, //  0: pull   block           side 1     
    0xa027, //  1: mov    x, osr                     
    0x80a0, //  2: pull   block                      
    0xa047, //  3: mov    y, osr                     
    0xb8e1, //  4: mov    osr, x          side 1     
    0x7110, //  5: out    pins, 16        side 0 [1] 
    0xb942, //  6: nop                    side 1 [1] 
    0x7108, //  7: out    pins, 8         side 0 [1] 
    0xb942, //  8: nop                    side 1 [1] 
    0x7108, //  9: out    pins, 8         side 0 [1] 
    0x1884, // 10: jmp    y--, 4          side 1     
            //     .wrap_target
    0x98a0, // 11: pull   block           side 1     
    0x7110, // 12: out    pins, 16        side 0 [1] 
    0xb942, // 13: nop                    side 1 [1] 
    0x7108, // 14: out    pins, 8         side 0 [1] 
    0xb942, // 15: nop                    side 1 [1] 
    0x7108, // 16: out    pins, 8         side 0 [1] 
    0x180b, // 17: jmp    11              side 1     
    0x98a0, // 18: pull   block           side 1     
    0x7100, // 19: out    pins, 32        side 0 [1] 
    0x180b, // 20: jmp    11              side 1     
    0xf822, // 21: set    x, 2            side 1     
    0xe000, // 22: set    pins, 0                    
    0x80a0, // 23: pull   block                      
    0x7000, // 24: out    pins, 32        side 0     
    0x003e, // 25: jmp    !x, 30                     
    0x98a0, // 26: pull   block           side 1     
    0xe001, // 27: set    pins, 1                    
    0x7108, // 28: out    pins, 8         side 0 [1] 
    0x19fc, // 29: jmp    !osre, 28       side 1 [1] 
    0x1856, // 30: jmp    x--, 22         side 1     
    0xe001, // 31: set    pins, 1                    
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program tft_io_program = {
    .instructions = tft_io_program_instructions,
    .length = 32,
    .origin = -1,
};

static inline pio_sm_config tft_io_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + tft_io_wrap_target, offset + tft_io_wrap);
    sm_config_set_sideset(&c, 2, true, false);
    return c;
}
#endif
