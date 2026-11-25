#include "uart.h"

void uart_init(void) {
    // 9600 bauds pour F_CPU = 16 MHz -> UBRR0 = 103
    UBRR0H = 0;
    UBRR0L = 103;
    UCSR0B = (1 << TXEN0);                  // Active uniquement l'envoi (TX)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 bits de données, 1 bit de stop
}

void uart_putc(char c) {
    while (!(UCSR0A & (1 << UDRE0))); // Attend que le buffer d'envoi soit prêt
    UDR0 = c;
}

void uart_print_u16(uint16_t val) {
    char buf[6];
    uint8_t i = 0;

    if (val == 0) {
        uart_putc('0');
    } else {
        while (val > 0) {
            buf[i++] = '0' + (val % 10);
            val /= 10;
        }
        while (i > 0) {
            uart_putc(buf[--i]);
        }
    }

    uart_putc('\r');
    uart_putc('\n');
}