# Wireless Mouse Security Analysis

## Contexte

Ce projet explore la sécurité des communications radio 2,4 GHz utilisées par les souris sans fil, à travers une approche pratique inspirée des recherches publiques sur la vulnérabilité MouseJack. L'objectif est de comprendre concrètement comment ces périphériques communiquent, et d'évaluer si les principes de sécurité de base (chiffrement, authentification des paquets) sont respectés.

Tous les tests sont réalisés exclusivement sur du matériel personnel, dans un cadre d'apprentissage.

## Objectifs

- Comprendre le fonctionnement du protocole radio 2,4 GHz utilisé par les souris sans fil
- Capturer et analyser le trafic radio d'une souris sans fil personnelle
- Identifier les éventuelles faiblesses de sécurité (absence de chiffrement, absence d'authentification)
- Documenter la méthodologie et les résultats de façon reproductible

## Matériel utilisé

- Arduino Nano (ATmega328, clone CH340)
- Module nRF24L01+ (x3, AZDelivery)
- Souris sans fil 2,4 GHz (cible de test, propriété personnelle)
- Kit de composants électroniques ELEGOO (breadboard, câbles, condensateurs)

## Étapes du projet

1. Préparation de l'environnement et du dépôt
2. Compréhension du matériel (Arduino, SPI, nRF24L01+, protocole radio)
3. Premiers montages et tests de communication entre modules
4. Capture et analyse du trafic radio de la souris cible
5. Analyse de sécurité (comparaison avec les vulnérabilités connues)
6. Scripts d'automatisation pour l'analyse des données
7. Documentation complète (schémas, captures, résultats)

## Statut

Projet en cours. Voir les commits pour l'avancement détaillé.

## Avertissement

Ce projet est mené uniquement à des fins éducatives, sur du matériel personnel. Aucun test n'est réalisé sur des appareils tiers sans autorisation.