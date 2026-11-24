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

Le module a été placé en mode "promiscuous" (écoute de tout le trafic) sur le
canal 23, avec une pseudo-adresse de 2 octets pour ne pas se limiter à un seul
émetteur.

Le CRC a volontairement été désactivé. En temps normal, le CRC est un code de
vérification qui fait rejeter par la radio tout paquet qui ne lui est pas
destiné. Or ici, on veut justement capter des paquets qui ne nous sont pas
adressés. CRC désactivé, la radio ne jette plus rien et laisse tout remonter,
y compris beaucoup de bruit radio, fait surtout de motifs de préambule répétés
(`0xAA` = 10101010 et `0x55` = 01010101).

Ce bruit a été filtré en logiciel, directement dans le programme : pour chaque
paquet de 32 octets, on compte les octets valant `0xAA` ou `0x55`. Si plus de la
moitié du paquet (16 octets) est ce préambule, le paquet est jeté comme du
bruit, sinon il est conservé comme vrai paquet candidat et affiché.

Deux captures ont ensuite été comparées : souris éteinte (témoin) et souris
allumée.

## Résultats

Une fois le bruit filtré, 11 paquets partageant une même signature
`9E 9E 96 54` sont apparus, répétés à l'identique. Cette signature est absente
de la capture témoin (souris éteinte).

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
  chiffrement ne produirait jamais de zéros propres : même "aucun mouvement"
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
- L'écoute est démontrée, mais l'injection de paquets n'a pas été testée.

## Suite

Décoder le rôle précis de chaque octet, puis étudier la faisabilité d'une
injection de paquets sur mon propre matériel.

## Cadre

Tests menés exclusivement sur du matériel personnel, à des fins d'apprentissage.
