##Branchements du LM35DZ## (Un vrai DZ comme on dit)

(je montre le point de vue depuis lequel regarder les branches)
 ____
/____\ (arrondi)
|____| (plat)
 | | |
 1 2 3

1 - 5V (peut changer mais c'est moins précis je crois, faut modifier le #define du driver)

2 - port analogique (A0-A5)

3 - GND

/!\ Lire une donnée analogique empêche la lecture parallèle d'autres données, l'ACL ne pouvait faire qu'une conversion à la fois. J'ignore le comportement de l'ACL si on ose modifier le channel (ADCASRA) pendant une conversion.