#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "timer.h"

// Faut connecter une led à PD3
// pour mieux voir on peut mettre OCR2A à 255
// et TCCR2B à 111 (avec CS20:22 = 1)

int main() {

    for(;;) {
        d_ir_timer_start();
        _delay_ms(2000);
        d_ir_timer_stop();
        _delay_ms(1000);
    }

    return 0;
}