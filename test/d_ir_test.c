#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "d_ir.h"
#include "s_led.h"
#include "d_led.h"
#include "uart.h"

int main() {
    uint16_t hits = 0;
    s_led s = { &DDRD, &PORTD, (1 << PD5) };
    extern volatile uint8_t d_ir_hit_flag;

    uart_init();
    d_ir_receiver_init();
    d_ir_timer_start();
    d_led_init(&s, 0);

    for (;;) {
        uint8_t triggered = 0;

        cli();
        if (d_ir_hit_flag) {
            d_ir_hit_flag = 0;
            triggered = 1;
        }
        sei();

        if (triggered) {
            EIMSK &= ~(1 << INT0);

            hits++;
            d_led_switch(&s);
            uart_print_u16(hits);

            _delay_ms(1000);
            EIFR |= (1 << INTF0);
            EIMSK |= (1 << INT0);
        }
    }
}