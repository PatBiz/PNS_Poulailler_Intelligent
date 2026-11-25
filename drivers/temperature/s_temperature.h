#pragma once
#include <avr/io.h>
#include <stdint.h>

/*
 * - channel : channel sur lequel est branché le capteur (A0=0, ...)
 */
typedef struct {
    uint8_t channel;  // from 0 to 5, c'est une valeur, pas un masque
} s_temperature;
