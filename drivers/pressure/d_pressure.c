#include "d_pressure.h"
#include "adc.h"

void d_pressure_read(const s_pressure *s, uint16_t *pressure) {
    if (!s) return;

    uint16_t adc_value;
    adc_read(s->channel, &adc_value);

    // formule trouvée sur internet
    *pressure = adc_value;
}