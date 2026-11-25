#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "s_led.h"
#include "d_led.h"

int main() {

    s_led s = { &DDRD, &PORTD, (1 << PD3) };  // D3
    
    d_led_init(&s, 0);

    for(;;) {
        d_led_switch(&s);
        _delay_ms(50);
    }

    return 0;
}