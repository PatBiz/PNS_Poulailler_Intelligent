#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "s_temperature.h"
#include "d_temperature.h"
#include "adc.h"
#include "uart.h"

int main() {
    adc_init();  // init de l'adc pour prendre les mesures analogiques
    uart_init();  // init du module pour qu'on puisse debug les valeurs

    s_temperature s = { 0 };  // A0

    uint16_t temperature;  // en dixième de °C

    for(;;) {
        d_temperature_read(&s, &temperature);
        uart_print_u16(temperature);

        _delay_ms(500);
    }

    return 0;
}