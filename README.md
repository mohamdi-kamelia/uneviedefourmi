# uneviedefourmi
# Une vie de fourmi

Ce projet simule les déplacements de fourmis dans une fourmilière modélisée sous forme de graphe. L’objectif est de déplacer toutes les fourmis du vestibule au dortoir en un minimum d’étapes, en respectant des règles strictes de capacité et de déplacement.

## Objectifs

- Modéliser une fourmilière comme un graphe orienté non pondéré.
- Implémenter les règles de déplacement des fourmis.
- Utiliser une architecture orientée objet en C++.
- Visualiser les étapes du déplacement.
- Compiler et organiser le projet avec CMake.

## Règles de simulation

- Toutes les fourmis commencent dans la salle d’entrée (le vestibule).
- Elles doivent rejoindre la salle de repos (le dortoir).
- Les salles intermédiaires ont une capacité limitée à une seule fourmi (sauf indication contraire).
- Une fourmi peut traverser un tunnel uniquement si la salle de destination est libre.
- Le vestibule et le dortoir peuvent accueillir plusieurs fourmis.
- Les tunnels sont traversés instantanément.
- Le but est de minimiser le nombre d’étapes nécessaires pour déplacer toutes les fourmis.

## Structure du projet

