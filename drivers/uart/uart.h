#pragma once

#include <avr/io.h>

void uart_init(void);
void uart_putc(char c);
void uart_print_u16(uint16_t val);
