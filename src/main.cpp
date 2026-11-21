#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10, 4000000);

// Canal a ecouter. On commence par un de ceux ou on a vu la souris.
// On pourra le changer (23, 20, 22, 25...) si on ne capte rien.
const uint8_t CANAL = 23;

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println(F("=== Sniffer promiscuous nRF24L01+ ==="));

  radio.begin();
  radio.setAutoAck(false);        // on n'accuse rien reception, on espionne
  radio.setChannel(CANAL);        // on se fixe sur un canal
  radio.setDataRate(RF24_2MBPS);  // vitesse supposee de la souris (a tester : 2MBPS puis 1MBPS)
  radio.disableCRC();             // on desactive le controle d'erreur pour ne rien jeter
  radio.setPayloadSize(32);       // taille max d'un paquet

  // Astuce "promiscuous" : adresse de 2 octets + pseudo-adresse,
  // pour capter les paquets de n'importe quel emetteur voisin.
  radio.setAddressWidth(2);
  radio.openReadingPipe(0, 0x00AALL);

  radio.startListening();
  Serial.print(F("Ecoute sur le canal "));
  Serial.println(CANAL);
}

void loop() {
  if (radio.available()) {
    uint8_t paquet[32];
    radio.read(paquet, 32);

    // On compte les octets "bruit" : AA et 55 sont les motifs du preambule.
    uint8_t bruit = 0;
    for (uint8_t i = 0; i < 32; i++) {
      if (paquet[i] == 0xAA || paquet[i] == 0x55) bruit++;
    }

    // Si plus de la moitie du paquet est du preambule, on l'ignore.
    if (bruit > 16) return;

    // Sinon, on affiche : candidat "vrai paquet".
    for (uint8_t i = 0; i < 32; i++) {
      if (paquet[i] < 16) Serial.print('0');
      Serial.print(paquet[i], HEX);
      Serial.print(' ');
    }
    Serial.println();
  }
}