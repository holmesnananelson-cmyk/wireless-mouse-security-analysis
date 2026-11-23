# MouseJack maison : analyser la sécurité d'une souris sans fil 2,4 GHz pour une vingtaine d'euros

Quand je bouge ma souris sans fil, ce qu'elle envoie à son récepteur USB
est-il chiffré, ou lisible par n'importe qui avec la bonne radio ? Je me suis
posé la question par curiosité, et pour pratiquer la cybersécurité sur un cas
réel plutôt que sur du cours. Réponse courte : sur la souris que j'ai testée,
ce n'est pas chiffré.

## Contexte

Les souris et claviers sans fil "classiques" (ni Bluetooth, ni filaires)
communiquent sur la bande 2,4 GHz avec une petite puce radio. En 2016,
l'équipe Bastille a montré avec la vulnérabilité MouseJack que beaucoup de ces
appareils n'avaient aucun chiffrement. Conséquence : on peut écouter ce qui
transite, et sur certains modèles injecter ses propres frappes à distance.

J'ai voulu refaire la partie "écoute" moi-même, sur ma propre souris, pour voir
si le problème existe encore.

## Matériel

- Arduino Nano (ATmega328P)
- Module radio nRF24L01+ (la même puce 2,4 GHz que dans les dongles grand public)
- Câbles Dupont femelle-femelle
- Une souris sans fil et son dongle USB (mon matériel personnel)

Coût total : une vingtaine d'euros.

## Démarche

### 1. Trouver où la souris émet

La bande 2,4 GHz est découpée en 126 canaux (2400 à 2525 MHz, un canal par MHz).
Impossible de tout écouter d'un coup, il fallait d'abord repérer les canaux
utilisés par la souris.

Méthode : j'ai balayé les 126 canaux avec le module radio et mesuré l'activité
sur chacun, une fois **souris éteinte**, une fois **souris allumée**. Comparer
les deux était indispensable, parce qu'en 2,4 GHz il y a déjà le Wi-Fi, le
Bluetooth et le reste : une seule mesure n'aurait rien prouvé.

Résultat : de l'activité qui n'apparaît que souris allumée, autour des canaux
20 à 25 (~2420-2425 MHz) et 113 à 115. La souris ne reste pas sur un canal, elle
en change en permanence : c'est du **frequency hopping**. La souris et le dongle
sautent de canal en canal de façon coordonnée, ce qui rend l'interception plus
difficile. Détail complet : [results/01-detection-canaux.md](results/01-detection-canaux.md).

### 2. Capturer les paquets

Une fois la plage connue, je me suis mis à l'écoute en mode "promiscuous" pour
attraper les paquets bruts, sans me faire passer pour le vrai récepteur.

Premier essai sans filtre : un déluge de bruit, inexploitable. En réactivant le
contrôle CRC (le mécanisme qui vérifie qu'un paquet n'est pas corrompu), le bruit
a disparu et des paquets propres et réguliers sont ressortis — uniquement quand
la souris était allumée. Détail complet :
[results/02-capture-paquets.md](results/02-capture-paquets.md).

Structure typique d'un paquet capturé :

    9E 9E 96 54 | 53 | 00 00 00 00 00 00 | 84 E9 73 75 | <octets variables>

## Résultat principal

Deux choses prouvent que ces paquets viennent bien de la souris :
- ils n'apparaissent jamais souris éteinte, et 11 fois souris allumée sur la même capture
- ils se répètent avec la même signature

Et deux choses prouvent que ce n'est pas chiffré :
- l'adresse de l'appareil est visible en clair et toujours identique
- la charge utile contient des suites de zéros bien nettes (00 00 00 00 00 00)

Si le contenu était chiffré, on ne verrait ni adresse fixe lisible, ni zéros
réguliers : un chiffrement transforme les données en quelque chose qui ressemble
à du hasard, sinon il ne sert à rien. Ici, rien de tout ça. La souris appartient
donc à la même classe de vulnérabilité que MouseJack.

## Limites

- Léger décalage de bits dans la capture (lié au fait qu'on n'utilise pas la
  vraie adresse du récepteur), donc tous les octets ne sont pas parfaitement alignés
- Le rôle exact de certains octets n'est pas encore décodé
- L'injection (envoyer de fausses frappes) n'a pas été testée

## Suite possible

- Décoder précisément le rôle de chaque octet du paquet
- Tester une injection sur mon propre matériel

## Cadre

Tout a été fait sur mon propre matériel, chez moi, dans un but d'apprentissage.
Écouter ou injecter sur le matériel d'autrui sans autorisation est illégal.
