#pragma once

#include <avr/io.h>
#include <stdint.h>

void adc_init();
void adc_read(const uint8_t channel, uint16_t *result);
