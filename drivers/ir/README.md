##Explication du fonctionnement##

Y'a 3 timers sur ATmega328P. Je momntre l'exemple du Timer2 pour commencer (faut voir en même temps que le code sinon ça veut rien dire).
Chaque timer a deux canaux A et B (deux comparateurs)

Timer2 est un compteur 8 bits (0 à 255) qui s'incrémente à chaque impulsion d'horloge

- TCNT2 (Timer/Counter Register 2) : valeur actuelle du compteur

- OCR2A (Output Compare Register 2 A) : valeur cible à atteindre

Le matériel compare TCNT2 à OCR2A en permanence.
En cas d'égalité ça enclenche un évènement de comparaison (Compare Match) et #si on l'active, TCNT2 est remis à 0# et #si on l'active, toogle OC2B qui active PD3#

- TCCR2A (Timer/Counter Control Register 2 A)
  - COM2B0 et COM2B1 (Compare Output Mode for Channel B) contrôlent OC2B
    - COM2B0=1 : mode Toogle OC2B on Compare Match
    - COM2B1=1 : mode Clear OC2B on Compare Match (PD3 reste bloquée à 0)
    - COM2B0 et 1 = 1 : mode Set OC2B on Compare Match (PD3 reste bloquée à 1)

  - WGM20, WGM21 et WGM22 (Waveform Generation Mode) : choix du mode de fonctionnement du timer
    (WG22 WG21 WG20 dans cet ordre)
    - 000 : mode Normal - compte de 0 à 255 puis déborde à 0
    - 010 : mode CTC (Clear Timer on Compare Match) - TCNT2 = 0 quand TCNT2 == OCR2A (A en particulier, B ne sera pas compabilisé)
    - 111 : mode Fast PWM : inutile là (pas compris aussi mdr)

- TCCR2B (Timer/Counter Control Register 2B)
  - CS20, CS21 et CS22 (Clock Select) : choix de la source d'horloge et du prédiviseur (ralenti le comptage)
    (CS22 CS21 CS20 dans cet ordre)
    - 000 : timer arrêté
    - 001 : horloge directe (16 MHz sur ATmega328P)
    - 010 : division par 8 (2 MHz)
    - 011 : division par 32 (500 kHz)
    - 100 : 64
    - 101 : 128
    - 110 : 256
    - 111 : 1024 (15.625 kHz)

Broches des timers/canaux
        Canal A     Canal B
Timer0  PD6 (OC0A)  PD5 (OC0B)
Timer1  PB1 (OC1A)  PB2 (OC1B)
Timer2  PB3 (OC2A)  PD3 (OC2B)

Le Timer1 est le seul en 16 bits.

Il faut donc choisir le pin de timer en fonction des canaux ou inversement.


##Explication de l'utilisation##

Le récepteur change tout seul sa valeur quand il ne reçoit pas la bonne fréquence (pas besoin de regarder ce qu'il reçoit).

On émet à 38kHz depuis l'emetteur (OC2B change PD3 directement faisant faciller l'émetteur).
Lorsque le récepteur ne reçoit plus, il passe à 1, interruption.
Dans l'interruption on dit "JE T4AI VUUUUUU :3"


##Explication de l'interruption##

Faire une interruption :
- dire à la puce quel port surveiller
- autoriser l'interrupteur (INT0 pour PD2 par exemple)
- ouvrir l'interrupteur général (sei() ou cli() pour fermer)

Pour def le comportement d'une interruption on écrit juste :
ISR(INT0_vect) {}
/!\ garder court (changement de variable /!\ volatile)

Registres importants :
- EICRA (External Interrupt Control Register A) - quel event déclenche l'interruption (sur 2 bits, ISC01 ISC00, dans cet ordre)
  - 00 : tant que la broche est à 0
  - 01 : à chaque changement
  - 10 : sur front descendant (passage de 1 à 0) -> ça pour l'ir
  - 11 : sur front momntant (passage de 0 à 1)

- EIMSK (External Interrupt Mask Regsiter) pour autoriser l'interruption de INT0 et/ou INT1
on a juste à mettre la valeur 1 ou 0 dcp
EIMSK |= (1 << INT0)

- EIFR (External Interrupt Falg Register) dit quelle interruption est levée à chaque survenance, remis à 0 automatiquement

- sei() cli() sont des fonctions de avr/interruption qui activent ou non les interruptions de manière globale.