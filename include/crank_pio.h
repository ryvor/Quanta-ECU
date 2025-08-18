#ifndef CRANK_PIO_H
#define CRANK_PIO_H
#include "hardware/pio.h"

#define crank_capture_program_length 4
extern const uint16_t crank_capture_program_instructions[crank_capture_program_length];
extern const struct pio_program crank_capture_program;

#endif
