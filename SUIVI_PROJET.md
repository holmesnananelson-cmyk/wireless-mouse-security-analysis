# Suivi du projet — Wireless Mouse Security Analysis

Fichier de suivi personnel. Coche les cases au fur et à mesure (`[ ]` -> `[x]`).
Place-le dans ton projet, par exemple : `~/Documents/PlatformIO/Projects/wireless-mouse-security-analysis/SUIVI_PROJET.md`

---

## Phase 0 — Préparation

### Environnement système
- [x] OS identifié : Linux Mint 22.2 (Zara), base Ubuntu 24.04
- [x] Python 3 déjà installé
- [x] Git déjà installé
- [x] Arduino IDE 2.3.4 installé (AppImage) dans `~/Applications/`
- [x] Arduino IDE ajouté au menu d'applications (icône extraite depuis l'AppImage)
- [x] VS Code installé via dépôt officiel Microsoft
- [x] Extension PlatformIO installée dans VS Code
- [x] Compte utilisateur ajouté au groupe `dialout` (accès port série)
- [ ] `pyserial` installé (`pip3 install pyserial --break-system-packages`)

### Projet PlatformIO
- [x] Projet créé : `wireless-mouse-security-analysis`
- [x] Carte configurée : Arduino Nano ATmega328 (corrigé après erreur ATmega168)
- [ ] Bibliothèque `RF24` ajoutée au projet
- [ ] Premier code de test compilé (blink LED)
- [ ] Premier code de test téléversé sur l'Arduino avec succès

### Dépôt GitHub
- [ ] Dépôt Git initialisé localement (`git init`)
- [ ] Dépôt distant créé sur GitHub (`wireless-mouse-security-analysis`)
- [ ] Structure de dossiers créée : `/docs` `/images` `/hardware` `/firmware` `/scripts` `/results` `/report`
- [ ] README.md rédigé (contexte, objectifs, matériel, étapes) — même sans code encore
- [ ] LICENSE ajoutée
- [ ] Premier commit + push

---

## Phase 1 — Comprendre le matériel

- [ ] Rôle de l'Arduino Nano compris (microcontrôleur, GPIO, alimentation)
- [ ] Notion de GPIO expliquée et comprise
- [ ] Protocole SPI expliqué et compris (comment il relie l'Arduino au module radio)
- [ ] Fonctionnement du nRF24L01+ compris (fréquence, canaux, adresses, ShockBurst)
- [ ] Fonctionnement radio d'une souris sans fil 2,4 GHz compris
- [ ] Contrainte d'alimentation 3,3V du module comprise (pourquoi pas 5V)
- [ ] Capable d'expliquer le matériel à quelqu'un d'autre sans notes

---

## Phase 2 — Premiers montages

- [ ] Test simple : LED + bouton sur breadboard (vérifier que l'Arduino et l'upload fonctionnent)
- [ ] Câblage du module nRF24L01+ sur l'Arduino Nano (SPI + alimentation 3,3V + condensateur)
- [ ] Code de vérification écrit (le module répond-il sur le bus SPI ?)
- [ ] Communication Arduino <-> module nRF24L01+ confirmée

---

## Phase 3 — Communication radio

- [ ] Notion d'adresse (adress/pipe) comprise
- [ ] Notion de canal comprise
- [ ] Notion de payload comprise
- [ ] Notion de CRC comprise
- [ ] Notion d'ACK (accusé de réception) comprise
- [ ] Code d'émission entre deux modules nRF24L01+ écrit et testé
- [ ] Code de réception écrit et testé
- [ ] Scan des canaux 2,4 GHz implémenté

---

## Phase 4 — Analyse de la souris

- [ ] Canal utilisé par la souris identifié
- [ ] Fréquence de transmission observée
- [ ] Régularité du trafic notée (constant ? par à-coups ?)
- [ ] Variation des paquets observée
- [ ] Présence d'un identifiant fixe vérifiée
- [ ] Observations documentées au fur et à mesure

---

## Phase 5 — Analyse de sécurité

- [ ] Comparaison avec les attaques connues (MouseJack) effectuée
- [ ] Protections présentes identifiées
- [ ] Protections absentes identifiées
- [ ] Risques réels évalués et formulés clairement
- [ ] Rappel écrit : tests uniquement sur mon propre matériel

---

## Phase 6 — Automatisation (scripts Python)

- [ ] Script de sauvegarde des captures
- [ ] Script d'analyse des données
- [ ] Script de génération de graphiques
- [ ] Script de statistiques

---

## Phase 7 — Documentation

- [ ] Schéma de câblage réalisé
- [ ] Photos du montage prises
- [ ] Schéma d'architecture du projet réalisé
- [ ] Captures d'écran des résultats
- [ ] Explications rédigées pour chaque étape clé

---

## Phase 8 — GitHub (finalisation)

- [ ] Structure finale du dépôt vérifiée et propre
- [ ] README complet et à jour
- [ ] Code commenté
- [ ] Historique de commits cohérent

---

## Phase 9 — LinkedIn

- [ ] Post rédigé : pourquoi ce projet
- [ ] Post rédigé : ce qui a été appris
- [ ] Post rédigé : difficultés rencontrées
- [ ] Post rédigé : résultats obtenus
- [ ] Post rédigé : perspectives d'amélioration
- [ ] Lien GitHub ajouté au post
- [ ] Publication faite

---

## Notes libres

(espace pour noter au fil de l'eau les problèmes rencontrés, solutions trouvées, questions à creuser)

