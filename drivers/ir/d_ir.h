#pragma once

#include <avr/io.h>
#include <stdint.h>
#include "s_ir.h"

void d_ir_emitter_start(const s_ir *s);
void d_ir_emitter_set(const s_ir *s, const uint8_t value);
void d_ir_receiver_init();