#include <avr/interrupt.h>
#include "d_ir.h"
#include "uart.h"

volatile uint8_t d_ir_hit_flag = 0;

ISR(INT0_vect) {
    d_ir_hit_flag = 1;
    uart_print_u16(1);
}

/*
 * faudrait faire un branchement pour qu'on puisse start/stop les émetteurs
 * les émetteurs sont connectés à PD3 qui oscille, il faut donc pouvoir empêcher
 * le courant d'aller dans tel ou tel émetteur (avec une porte &)
 * je sais pas faire ça en élec mais on doit trouver ez
 */
void d_ir_emitter_start(const s_ir *s) {
    if (!s) return;

    *(s->ddr) |= s->mask;  // output
    *(s->port) &= ~s->mask;  // init à 0
}

void d_ir_emitter_set(const s_ir *s, const uint8_t value) {
    if (!s) return;

    // on reset le port à 0 puis on mets la valeur
    *(s->port) = (*(s->port) & ~s->mask) | ((value & 0b1) * s->mask);
}


void d_ir_receiver_init() {
    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2);

    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);

    EIMSK |= (1 << INT0);
    sei();
}