#pragma once

#include <avr/io.h>
#include <stdint.h>

typedef struct {
    volatile uint8_t *ddr;
    volatile uint8_t *port;
    uint8_t mask;  // pin sur laquelle on connecte
} s_ir;
