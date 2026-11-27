##Forward le port à WSL :##
(PowerShell admin)

$> usbipd list

trouver le port de l'arduino

$> usbipd bind --busid 1-4

(avec 1-4 le port trouvé)

$> usbipd attach --wsl --busid 1-4


##Lire le moniteur série avec UART (100\% Gemini)###

$> ls -l /dev/ttyACM* /dev/ttyUSB* 2>/dev/null

permet de trouver le périphérique de comm (def dans le Makefile actuel)

$> stty -F /dev/ttyACM0 9600 raw -echo && cat /dev/ttyACM0

affiche le port série


##Makefile use (histoire de simplifier le pavé)##

Compiler les drivers :

$> make drivers

Compiler un test : (contient un main donc doit être compilé seul)

$> make test

Upload dans l'arduino : (avec le nom du test compilé en arg)

$> make upload PROG=test