# Résultat 01 — Détection de la souris sur la bande 2,4 GHz

## Objectif

Vérifier si une souris sans fil 2,4 GHz émet un signal radio détectable, et
identifier sur quels canaux elle est active, à l'aide d'un montage
Arduino Nano + module nRF24L01+.

## Matériel

- Arduino Nano (ATmega328, clone CH340)
- Module radio nRF24L01+ (AZDelivery)
- Souris sans fil 2,4 GHz personnelle, avec son dongle USB
- Liaison SPI directe entre le module et l'Arduino (câbles femelle-femelle)

## Méthode

Le code `src/main.cpp` fait office de scanner : il parcourt les 126 canaux de
la bande 2,4 GHz (canal N = 2400 + N MHz) et mesure, pour chacun, la présence
d'un signal. Chaque canal est sondé 100 fois par passage. Le résultat s'affiche
sous forme d'un caractère par canal, de `0` (aucune activité) à `f` (activité
maximale).

Pour isoler la souris du bruit de fond (Wi-Fi, Bluetooth voisins), une
comparaison contrôlée a été menée en ne changeant qu'un seul paramètre :

1. Souris **éteinte** (interrupteur sur OFF, dongle resté branché) — mesure de
   référence du bruit ambiant.
2. Souris **allumée et déplacée** en continu, près du module.

L'activité moyenne par canal a été calculée pour chaque situation, puis la
différence des deux. Ce qui augmente nettement en passant de "éteinte" à
"allumée" correspond à l'émission propre de la souris.

Remarque de méthode : un premier essai avait gardé la souris allumée pendant la
phase "repos", ce qui ne permettait aucune comparaison valable. Couper
complètement la source est indispensable pour obtenir une référence fiable.

## Résultats

Canaux dont l'activité augmente le plus quand la souris passe de éteinte à
allumée :

| Canal | Fréquence | Éteinte | Allumée | Hausse |
|-------|-----------|---------|---------|--------|
| 23    | 2423 MHz  | 0,2     | 4,9     | +4,7   |
| 21    | 2421 MHz  | 2,7     | 6,6     | +3,9   |
| 20    | 2420 MHz  | 3,2     | 7,0     | +3,8   |
| 115   | 2515 MHz  | 0,3     | 3,6     | +3,2   |
| 22    | 2422 MHz  | 2,0     | 5,1     | +3,1   |
| 25    | 2425 MHz  | 0,3     | 3,0     | +2,7   |
| 113   | 2513 MHz  | 1,3     | 3,9     | +2,5   |

Deux groupes de canaux ressortent clairement : autour de 2420-2425 MHz
(canaux 20 à 25) et autour de 2513-2515 MHz (canaux 113-115).

## Interprétation

La souris possède une empreinte radio nette, répartie sur plusieurs groupes de
canaux éloignés. Ce comportement correspond au saut de fréquence
(frequency hopping) : la souris change constamment de canal pendant qu'elle
communique, au lieu d'en occuper un seul. Cela lui permet de résister aux
interférences, un canal encombré ne bloquant la liaison que très brièvement.

La souris et son dongle USB sautent de façon synchronisée, en suivant la même
séquence de canaux au même moment. Sans cette synchronisation, ils ne
pourraient plus se trouver sur le même canal pour échanger.

Un essai antérieur avait observé l'activité plutôt vers les canaux 37-40. Le
fait de la retrouver ici sur d'autres canaux confirme ce balayage permanent de
la bande.

## Limites

- Le scanner détecte une présence de signal, pas son contenu : il ne dit pas
  encore si les données sont chiffrées.
- La bande 2,4 GHz est partagée avec le Wi-Fi et le Bluetooth, qui restent
  présents en bruit de fond.
- Les mesures dépendent de la distance souris-module et de l'environnement
  radio du moment.

## Prochaine étape

Passer de la détection de présence à la capture des paquets émis par la souris,
pour examiner leur contenu et répondre aux questions de sécurité : les données
sont-elles chiffrées, existe-t-il un identifiant fixe, une protection contre
l'injection.

## Cadre

Tests réalisés uniquement sur du matériel personnel, à des fins d'apprentissage.
