#include "ants.hpp"
#include <fstream>
#include <sstream>

void chargerDepuisFichier(const std::string& chemin, Fourmiliere& f) {
    std::ifstream fichier(chemin);
    if (!fichier) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return;
    }

    std::string ligne;
    enum Section { AUCUNE, SALLES, TUNNELS, FOURMIS } section = AUCUNE;

    while (std::getline(fichier, ligne)) {
        if (ligne.empty()) continue;

        if (ligne == "Salles:") {
            section = SALLES;
        } else if (ligne == "Tunnels:") {
            section = TUNNELS;
        } else if (ligne == "Fourmis:") {
            section = FOURMIS;
        } else {
            std::istringstream iss(ligne);
            if (section == SALLES) {
                std::string nom;
                int capacite;
                iss >> nom >> capacite;
                f.ajouterSalle(nom, capacite);
                if (nom == "Sv") f.vestibule = f.salles[nom];
                if (nom == "Sd") f.dortoir = f.salles[nom];
            } else if (section == TUNNELS) {
                std::string s1, s2;
                iss >> s1 >> s2;
                f.ajouterTunnel(s1, s2);
            } else if (section == FOURMIS) {
                std::string id;
                iss >> id;
                f.ajouterFourmi(id);
            }
        }
    }
}

int main() {
    Fourmiliere f;
    chargerDepuisFichier("./data/exemple1.txt", f);
    f.afficherGraphe();
    f.simulerDeplacement();
    return 0;
}
