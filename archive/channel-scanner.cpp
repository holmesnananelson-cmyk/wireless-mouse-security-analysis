// channel-scanner.cpp - Firmware de la PHASE 1 (detection des canaux).
// A servi a reperer les canaux 2,4 GHz utilises par la souris (voir
// results/01-detection-canaux.md). Archive ici car src/main.cpp a ensuite
// ete reutilise pour la phase 2 (le sniffer). Pour le relancer : recopier
// ce contenu dans src/main.cpp puis televerser.

#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>

// On cree l'objet "radio" qui pilote le module.
// (9, 10) = broches CE et CSN. 4000000 = vitesse SPI a 4 MHz (plus tolerante au cablage).
RF24 radio(9, 10, 4000000);

// Le module nRF24L01+ couvre 126 canaux (de 0 a 125).
// Chaque canal correspond a une frequence : 2400 MHz + numero du canal.
// Exemple : canal 76 = 2476 MHz.
const uint8_t NOMBRE_CANAUX = 126;

// Un tableau pour compter, a chaque passage, combien de fois un signal
// a ete detecte sur chaque canal.
uint8_t valeurs[NOMBRE_CANAUX];

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  Serial.println(F("=== Scanner de canaux 2.4 GHz ==="));

  // On demarre le module.
  if (!radio.begin()) {
    Serial.println(F("ERREUR : le module ne repond pas. Verifie le cablage."));
    while (true) {}  // On bloque ici, inutile de continuer sans module.
  }

  // Configuration pour l'ecoute passive :
  radio.setAutoAck(false);  // On n'envoie pas d'accuse de reception : on observe, c'est tout.
  radio.stopListening();    // On part d'un etat propre avant de scanner.

  // On affiche l'en-tete : les numeros de canaux en hexadecimal, lus verticalement.
  Serial.print(F("Canaux (0 a 125) : "));
  for (uint8_t canal = 0; canal < NOMBRE_CANAUX; canal++) {
    Serial.print(canal >> 4, HEX);  // chiffre des dizaines (hex) du numero de canal
  }
  Serial.println();
  Serial.print(F("                   "));
  for (uint8_t canal = 0; canal < NOMBRE_CANAUX; canal++) {
    Serial.print(canal & 0xF, HEX);  // chiffre des unites (hex) du numero de canal
  }
  Serial.println();
}

void loop() {
  // Nombre de fois qu'on va sonder chaque canal a chaque tour de boucle.
  // Plus ce nombre est eleve, plus la mesure est fiable (mais plus lente).
  const int REPETITIONS = 100;

  // On remet tous les compteurs a zero avant un nouveau balayage.
  memset(valeurs, 0, sizeof(valeurs));

  // On sonde chaque canal, REPETITIONS fois.
  for (int rep = 0; rep < REPETITIONS; rep++) {
    for (uint8_t canal = 0; canal < NOMBRE_CANAUX; canal++) {
      radio.setChannel(canal);   // On se place sur le canal a tester.

      radio.startListening();    // On active la reception (le module "ecoute").
      delayMicroseconds(130);    // On laisse 130 microsecondes au module pour capter.
      radio.stopListening();     // On arrete d'ecouter.

      // testCarrier() renvoie vrai si un signal a ete detecte pendant l'ecoute.
      if (radio.testCarrier()) {
        valeurs[canal]++;        // On incremente le compteur de ce canal.
      }
    }
  }

  // On affiche le resultat : un chiffre hex par canal (0 = rien, f = tres actif).
  for (uint8_t canal = 0; canal < NOMBRE_CANAUX; canal++) {
    // On plafonne a 15 (f en hex) pour tenir sur un seul caractere.
    uint8_t niveau = min((uint8_t)0xF, valeurs[canal]);
    Serial.print(niveau, HEX);
  }
  Serial.println();
}
