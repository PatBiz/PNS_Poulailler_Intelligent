#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "s_pressure.h"
#include "d_pressure.h"
#include "adc.h"
#include "uart.h"

int main() {
    adc_init();  // init de l'adc pour prendre les mesures analogiques
    uart_init();  // init du module pour qu'on puisse debug les valeurs

    s_pressure s = { 0 };  // A0

    uint16_t pressure;  // en kP

    for(;;) {
        d_pressure_read(&s, &pressure);
        uart_print_u16(pressure);

        _delay_ms(500);
    }

    return 0;
}