# Résultat 02 — Capture des paquets et absence de chiffrement

## Objectif

Capturer les paquets réellement échangés entre la souris et son dongle, et
examiner leur contenu afin de déterminer si les données sont chiffrées ou
transmises en clair.

## Matériel

- Arduino Nano (ATmega328, clone CH340)
- Module radio nRF24L01+ (AZDelivery)
- Souris sans fil 2,4 GHz personnelle, avec son dongle USB
- Canal d'écoute : 23 (2423 MHz), identifié au Résultat 01 comme le canal où la
  souris était la plus active

## Méthode

Le module a été placé en mode « promiscuous » (écoute de tout le trafic) sur le
canal 23, avec une pseudo-adresse de 2 octets pour ne pas se limiter à un seul
émetteur.

Une première capture, CRC désactivé, a produit un flot continu de paquets
d'apparence aléatoire — du bruit — que la souris soit allumée ou éteinte. Les
vrais paquets de la souris y étaient noyés et indistinguables.

Le CRC a ensuite été réactivé (16 bits). Le CRC est un petit code de
vérification ajouté à chaque paquet : le récepteur recalcule ce code et ne garde
que les paquets dont le résultat correspond. Un paquet de bruit aléatoire a une
probabilité infime d'avoir un CRC valide, il est donc rejeté, tandis qu'un vrai
paquet de la souris passe. Cette simple validité suffit à filtrer la quasi-
totalité du bruit.

Deux captures ont été comparées : souris éteinte (témoin) et souris allumée.

## Résultats

La capture avec CRC a fait apparaître 11 paquets partageant une même signature
`9E 9E 96 54`, répétés à l'identique. Cette signature est absente de la capture
témoin (souris éteinte).

| Capture          | Paquets `9E 9E 96 54` |
|------------------|-----------------------|
| Souris éteinte   | 0                     |
| Souris allumée   | 11                    |

À titre de comparaison, les séquences de bruit n'apparaissent chacune qu'une
seule fois.

Structure observée des paquets de la souris :

```
9E 9E 96 54 | 53 | 00 00 00 00 00 00 | 84 E9 73 75 | <fin variable>
  adresse    ctrl     charge utile       signature
```

- `9E 9E 96 54` : adresse, identique sur tous les paquets
- `53` / `55` / `51` : champ de contrôle, légèrement variable
- `00 00 00 00 00 00` : charge utile, souvent à zéro
- `84 E9 73 75` : seconde séquence fixe

## Interprétation

Deux indices montrent que ces paquets sont bien ceux de la souris, et non du
bruit :

- La signature n'apparaît que lorsque la souris est allumée (0 contre 11).
- Elle se répète à l'identique, alors que le bruit, aléatoire, ne se répète
  jamais.

Deux indices montrent que les données sont transmises en clair, et non
chiffrées :

- L'adresse `9E 9E 96 54` est fixe et lisible. Un chiffrement la rendrait
  d'apparence aléatoire et la ferait varier d'un paquet à l'autre.
- La charge utile vaut `00 00 00 00 00 00` quand la souris ne bouge pas. Un
  chiffrement ne produirait jamais de zéros propres : même « aucun mouvement »
  ressortirait brouillé.

La communication de la souris n'est donc pas chiffrée. Son adresse étant de plus
visible et fixe, un tiers à portée peut l'identifier et écouter son trafic. Cela
correspond à la classe de vulnérabilité décrite par la recherche MouseJack.

## Limites

- Le mode de capture peut décaler les octets de quelques bits : la valeur exacte
  de l'adresse et les frontières des champs ne sont pas garanties. La conclusion
  (répétition et zéros incompatibles avec un chiffrement) reste valable.
- La structure est identifiée, mais le rôle précis de chaque octet (boutons,
  déplacements X et Y) n'est pas encore décodé.
- L'écoute est démontrée ; l'injection de paquets n'a pas été testée.

## Suite

Décoder le rôle précis de chaque octet, puis étudier la faisabilité d'une
injection de paquets — étape qui nécessiterait vraisemblablement du matériel
spécialisé (type Crazyradio).

## Cadre

Tests menés exclusivement sur du matériel personnel, à des fins d'apprentissage.
