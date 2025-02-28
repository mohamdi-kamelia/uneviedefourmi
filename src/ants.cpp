#include "../include/ants.hpp"

// Constructeur de la fourmi
Fourmi::Fourmi(int id, std::string position) : id(id), position(position) {}


Salle::Salle(std::string nom, int capacite) : nom(nom), capacite(capacite) {}


void Salle::ajouterConnexion(std::string salle) {
    connexions.push_back(salle);
}


Fourmiliere::Fourmiliere(std::string entree, std::string sortie) : entree(entree), sortie(sortie) {}

// Ajouter une salle à la fourmilière
void Fourmiliere::ajouterSalle(std::string nom, int capacite) {
    salles[nom] = Salle(nom, capacite);
}

// Ajouter un tunnel entre deux salles
void Fourmiliere::ajouterTunnel(std::string salle1, std::string salle2) {
    salles[salle1].ajouterConnexion(salle2);
    salles[salle2].ajouterConnexion(salle1);
}

// Trouver le plus court chemin entre deux salles (BFS)
std::vector<std::string> Fourmiliere::trouverChemin(std::string depart, std::string arrivee) {
    std::queue<std::vector<std::string>> queue;
    queue.push({depart});
    std::unordered_map<std::string, bool> visite;
    
    while (!queue.empty()) {
        auto chemin = queue.front();
        queue.pop();
        std::string salle_actuelle = chemin.back();

        if (salle_actuelle == arrivee) return chemin;

        if (visite[salle_actuelle]) continue;
        visite[salle_actuelle] = true;

        for (auto &voisin : salles[salle_actuelle].connexions) {
            if (!visite[voisin]) {
                auto nouveau_chemin = chemin;
                nouveau_chemin.push_back(voisin);
                queue.push(nouveau_chemin);
            }
        }
    }
    return {};
}

// Déplacer toutes les fourmis du vestibule au dortoir
void Fourmiliere::deplacerFourmis() {
    for (auto &fourmi : fourmis) {
        std::vector<std::string> chemin = trouverChemin(entree, sortie);
        
        for (size_t i = 1; i < chemin.size(); ++i) {
            std::cout << "Étape " << i << " : Fourmi " << fourmi.id << " -> " << chemin[i] << std::endl;
            fourmi.position = chemin[i];
        }
    }
}
