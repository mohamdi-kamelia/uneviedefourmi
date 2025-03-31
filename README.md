# Une vie de fourmi

## Description

Ce projet simule le déplacement d'une colonie de fourmis depuis le vestibule (entrée) jusqu'au dortoir (salle de repos) dans une fourmilière représentée sous forme de graphe.  
L'objectif est de déplacer toutes les fourmis en un **minimum d'étapes**, en respectant les **contraintes de capacité** et d’occupation des salles.

## Objectifs

- Représenter la fourmilière comme un graphe non orienté.
- Implémenter un système de déplacement respectant les règles imposées.
- Simuler les mouvements des fourmis de manière optimisée.
- Afficher les déplacements étape par étape dans le terminal.
- Exporter les graphes de simulation au format `.dot` (compatible Graphviz).

## Fonctionnalités

- Chargement automatique de tous les fichiers de fourmilière (`.txt`) depuis le dossier `data/`.
- Détection automatique du format de fichier (`classique` ou `alternatif`).
- Simulation étape par étape du déplacement de toutes les fourmis.
- Gestion de la capacité des salles et des règles de déplacement.
- Affichage dans le terminal de la position de chaque fourmi à chaque étape.
- Export automatique des graphes de simulation (format `.dot`) dans le dossier `output/`.

## Technologies utilisées

- **Langage :** C++17
- **Compilation :** CMake
- **Visualisation (optionnel) :** Graphviz (pour `.dot` → `.png`)

## Organisation du projet

.
├── include/  
│   └── ants.hpp  
├── src/  
│   └── ants.cpp  
├── data/  
│   └── (fichiers .txt de fourmilières)  
├── output/  
│   └── (fichiers .dot exportés à chaque étape)  
├── main.cpp  
├── CMakeLists.txt  
└── README.md  

## Compilation

Ouvrir un terminal dans le dossier du projet et exécuter :

```bash
mkdir build
cd build
cmake ..
cmake --build .
