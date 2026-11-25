#include "adc.h"

void adc_init() {
    /*
     * admux 8 bits :
     * - 7-6 : ref de tension 00=AREF, 01=AVCC (5V), 11=Interne 1.1V
     * - 5 : ADLAR alignement à gauche (pas compris j'y touche pas)
     * - 4 : jsp pas touche
     * - 3-0 : sélection du canal (0000=ADC0, 0101=ADC5, ...)
     * 3-0 permet de coder 16 chiffres, au delà de 5, c'est des trucs spéciques à la carte (1000 est un capteur de température intégré)
     */
    ADMUX = (1 << REFS0);  // référence de tension à 5V (REFS0=reference selection bit 0)

    /*
     * adcsra 8 bits
     * - 7 ADEN : ADC Enable - active l'adc
     * - 6 ADSC : ADC Start Conversion - lance une conversion
     * - 5 ADATE : m'intéresse pas
     * - 4 ADIF : ADC Interrupt Flag - passe à 1 à la fin d'une conversion (ne se remet pas à 0 seul, donc on pref utiliser ADSC=0 pour suivre la fin d'une conversion)
     * - 3 ADIE : ADC Interrupt Enable - active l'interruption ADC
     * - 2-0 ADPS2-0 : Prescaler - je crois que ça règle la freq de l'horloge, à set à 111=128, c'est opti pour la résolution de ATmega328P
     */
    ADCSRA = (1 << ADEN)  // on active l'ADC
        | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // on mets le prescaler à 128 comme explique en commentaire
}

void adc_read(const uint8_t channel, uint16_t *result) {
    // sélection du canal admux
    // 0xF0 = 11110000 (pour garder les params d'admux)
    // 0x0F = 00001111 (pour garder le channel)
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

    // lancement convertion
    ADCSRA |= (1 << ADSC);

    // attendre fin conversion
    while (ADCSRA & (1 << ADSC));

    *result = ADC;
}
