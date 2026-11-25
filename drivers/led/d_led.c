#include "d_led.h"

void d_led_init(const s_led *s, const uint8_t init_value) {
    if (!s) return;

    *(s->ddr) |= s->mask;  // output

    if (init_value) {  // setting init value
        *(s->port) |= s->mask;  // init à 1
    } else {
        *(s->port) &= ~s->mask;  // init à 0
    }
}

void d_led_set(const s_led *s, const uint8_t value) {
    if (!s) return;

    // on reset le port à 0 puis on mets la valeur
    *(s->port) = (*(s->port) & ~s->mask) | ((value & 0b1) * s->mask);
}

void d_led_switch(const s_led *s) {
    if (!s) return;

    *(s-> port) ^= s->mask;
}
