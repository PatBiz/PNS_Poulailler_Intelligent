#pragma once

#include <avr/io.h>
#include <stdint.h>
#include "s_pressure.h"

void d_pressure_read(const s_pressure *s, uint16_t *pressure);