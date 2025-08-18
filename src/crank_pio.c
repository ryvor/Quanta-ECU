#include "crank_pio.h"

const uint16_t crank_capture_program_instructions[crank_capture_program_length] = {
    0x2020, // wait 1 pin 0
    0x0000, // irq 0 (placeholder)
    0x20a0, // wait 0 pin 0 (placeholder)
    0x0005  // jmp 0 (placeholder)
};

const struct pio_program crank_capture_program = {
    .instructions = crank_capture_program_instructions,
    .length = crank_capture_program_length,
    .origin = -1,
};
