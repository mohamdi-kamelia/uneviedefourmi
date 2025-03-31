#include "ants.hpp"

Salle::Salle(std::string nom, int capacite) : nom(nom), capacite(capacite) {}

Fourmi::Fourmi(std::string id, Salle* position) : id(id), position(position) {}

void Fourmiliere::ajouterSalle(std::string nom, int capacite) {
    salles[nom] = new Salle(nom, capacite);
}

void Fourmiliere::ajouterTunnel(std::string s1, std::string s2) {
    if (salles.count(s1) && salles.count(s2)) {
        salles[s1]->connexions.push_back(salles[s2]);
        salles[s2]->connexions.push_back(salles[s1]);
    }
}

void Fourmiliere::ajouterFourmi(std::string id) {
    Fourmi f(id, vestibule);
    fourmis.push_back(f);
}

void Fourmiliere::afficherGraphe() {
    std::cout << "Graphe de la fourmiliere :\n";
    for (auto& [nom, salle] : salles) {
        std::cout << salle->nom << " reliee e : ";
        for (auto& adj : salle->connexions) {
            std::cout << adj->nom << " ";
        }
        std::cout << "\n";
    }
}

void Fourmiliere::simulerDeplacement() {
    std::cout << "\n+++ Simulation du deplacement +++\n";

    int etape = 1;
    int index = 0;

    while (index < fourmis.size()) {
        std::cout << "+++ E " << etape << " +++\n";
        int nb = 0;
        for (auto& f : fourmis) {
            if (f.position == vestibule && nb < 2) { // 2 max par étape
                std::cout << f.id << " - " << f.position->nom << " - Sd\n";
                f.position = dortoir;
                index++;
                nb++;
            }
        }
        etape++;
    }

    std::cout << "\nToutes les fourmis sont arrivees au dortoir.\n";
}
