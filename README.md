# Mannette USB

Projet tutoré de manette USB Atmega32u4.

## Pour commencer

Voici les instructions vous permettant de tester notre programme sur une manette.

### Prérequis

Il est nécessaire d'installer la librairie libusb.

```
sudo apt install libusb-1.0-0-dev
```

Vous pouvez ensuite cloner notre projet de la façon suivante.

```
git clone https://archives.plil.fr/cvingere/vingere-ziani-manette-usb.git
```

### Installation

Il faudra tout d'abord se rendre dans le dossier suivant et effectuer la commande make : 

```
vingere-ziani-manette-usb/lufa-LUFA-170418/PolytechLille/Manette
```
On pourra ensuite téléverser le programme dans la manette. 
Le paquetage Debian dfu-programmer est nécessaire.

On effectuera les commandes suivantes :

```
dfu-programmer atmega32u4 erase
dfu-programmer atmega32u4 flash Manette.hex
dfu-programmer atmega32u4 reset
```
Il faudra finalement débrancher puis rebrancher la manette. Le programme devrait maintenant être dans actif sur la carte.


Pour compiler le programme de test de la manette :

```
gcc -Wall -o main main.c -lusb-1.0
```

## Lancer le test

```
./main
```

### À propos du test

Vous devrez d'abord renseigner l'ID Vendeur puis l'ID Produit.  
Ensuite vous pourrez choisir entre tester l'allumage d'une seule LED (fonctionnel)
ou le chenillard (non testé).  
Les vibreurs ne sont pas pris en compte.
Seul un bouton fonctionne correctement (le bouton haut), les autres ne sont pas fonctionnels, ou n'ont pas été testés.
Les interfaces pour les leds et le vibreurs ont été créés ainsi que leur endpoint respectif.
Les codes qui gèrent le joystick, les leds et les boutons sont situé ici : 

```
vingere-ziani-manette-usb/lufa-LUFA-170418/LUFA/Drivers/Board/AVR8/MZB
```



## Auteurs

- **Merwane Ziani Bey** - _Programme ATMega32u4_ - [mzianibe](https://archives.plil.fr/u/mzianibe)
- **Camille Vingere** - _Contrôle de la manette_ - [cvingere](https://archives.plil.fr/u/cvingere)
