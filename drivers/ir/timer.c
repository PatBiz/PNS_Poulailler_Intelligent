#include "timer.h"

/*
 * Timer hardcoded car il faut choisir le timer, le canal, le pin, ...
 * en vrai c'est faisable, mais le nombre d'args dépend du niveau de modularité qu'on veut
 * Fait vasciller PD3 à ~38.1kHz (freq idéal de nos émetteurs IR)
 */
void d_ir_timer_start() {
    DDRD |= (1 << PD3);  // pin qui oscillera
    TCNT2 = 0;  // init du compteur pour bien partir
    OCR2A = 209;  // donne la freq de vascillement (16MHz / (2*prédiviseur*(1+OCR2A)) = ~38.1kHz)
    TCCR2A = (1 << COM2B0) | (1 << WGM21);  // Compare Match sur OC2B->PD3 + mode CTC
    TCCR2B = (1 << CS20);  // horloge directe, prédiviseur = 1 => 16MHz
}

void d_ir_timer_stop() {
    TCCR2B = 0;  // CS22:20 = 000 => timer arrêté
    TCCR2A = 0;  // on retire la config du timer
    PORTB &= ~(1 << PD3);  // on remet PD3 à 0
}
