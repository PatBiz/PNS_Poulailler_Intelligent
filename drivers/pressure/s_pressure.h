#pragma once

#include <avr/io.h>
#include <stdint.h>

/*
 * - channel : channel sur lequel est branché le capteur (A0=0, ...)
 */
typedef struct {
    uint8_t channel;  // de 0 à 5, c'est une valeur, pas un masque
} s_pressure;