#pragma once

#include <avr/io.h>
#include <stdint.h>
#include "s_temperature.h"

// temperature en dixième de °C
void d_temperature_read(const s_temperature *s, uint16_t *temperature);
