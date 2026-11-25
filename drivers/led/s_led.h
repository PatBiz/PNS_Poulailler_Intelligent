#pragma once
#include <stdint.h>

/*
 * - ddr : registre des canaux digitaux
 * - port : port de la pin (A, B, C, D) dans le cas d'autres cartes
 * - mask : bit de la pin
 */
typedef struct {
    volatile uint8_t *ddr;
    volatile uint8_t *port;
    uint8_t mask;
} s_led;
