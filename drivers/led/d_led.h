#pragma once

#include <avr/io.h>
#include <stdint.h>
#include "s_led.h"

void d_led_init(const s_led *s, const uint8_t init_value);
void d_led_set(const s_led *s, const uint8_t value);
void d_led_switch(const s_led *s);