#include "d_temperature.h"
#include "adc.h"

// voltage reference du lm35 (on peut mettre 3.3 ou 1.1)
#define VREF 5000

void d_temperature_read(const s_temperature *s, uint16_t *temperature) {
    if (!s) return;
    
    uint16_t adc_value;
    adc_read(s->channel, &adc_value);

    /*
     * - VREF : tension en mV du capteur
     * - 1024 : résolution de la valeur adc (va de 0 à 1023)
     * - +512 : on arrondi avant de diviser, vu que ça va couper la valeur on veut un arrondi correct (0,5->1)
     * on doit passer un uint32_t car pdt la multiplication la valeur peut aller jusqu'à 1048576
     * calcul en mV car on a pas de float
     */
    uint16_t voltage = (uint16_t)(((uint32_t)adc_value * VREF + 512) / 1024);
    
    // 1mv = 0.1°C, on garde en dixième de degré
    *temperature = voltage;
}
