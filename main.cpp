#include "ants.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

namespace fs = std::filesystem;

// Chargement de fourmilière en format alternatif (f=, Sx {cap}, tunnels)
void chargerFourmiliereFormatAlternatif(const std::string& chemin, Fourmiliere& f) {
    std::ifstream fichier(chemin);
    std::string ligne;
    int nbFourmis = 0;

    while (std::getline(fichier, ligne)) {
        if (ligne.empty()) continue;

        // Lire le nombre de fourmis
        if (ligne.rfind("f=", 0) == 0) {
            nbFourmis = std::stoi(ligne.substr(2));
            continue;
        }

        // Définir une salle (avec ou sans capacité)
        if (ligne.find("-") == std::string::npos) {
            std::string nom;
            int capacite = 1;

            size_t pos_ouverture = ligne.find("{");
            size_t pos_fermeture = ligne.find("}");

            if (pos_ouverture != std::string::npos && pos_fermeture != std::string::npos) {
                nom = ligne.substr(0, pos_ouverture - 1);
                capacite = std::stoi(ligne.substr(pos_ouverture + 1, pos_fermeture - pos_ouverture - 1));
            } else {
                nom = ligne;
            }

            f.ajouterSalle(nom, capacite);
            if (nom.find("Sv") != std::string::npos) f.vestibule = f.salles[nom];
            if (nom.find("Sd") != std::string::npos) f.dortoir = f.salles[nom];
        }

        // Définir un tunnel
        else {
            std::string s1, s2;
            std::replace(ligne.begin(), ligne.end(), '-', ' ');
            std::istringstream iss(ligne);
            iss >> s1 >> s2;
            f.ajouterTunnel(s1, s2);
        }
    }

    // Créer automatiquement les fourmis
    for (int i = 1; i <= nbFourmis; ++i) {
        f.ajouterFourmi("f" + std::to_string(i));
    }
}

// Chargement format classique (Salles:, Tunnels:, Fourmis:)
void chargerFourmiliereFormatClassique(const std::string& chemin, Fourmiliere& f) {
    std::ifstream fichier(chemin);
    std::string ligne;
    enum Section { AUCUNE, SALLES, TUNNELS, FOURMIS } section = AUCUNE;

    while (std::getline(fichier, ligne)) {
        if (ligne.empty()) continue;

        if (ligne == "Salles:") section = SALLES;
        else if (ligne == "Tunnels:") section = TUNNELS;
        else if (ligne == "Fourmis:") section = FOURMIS;
        else {
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
    std::string dossier = "./data";

    for (const auto& entry : fs::directory_iterator(dossier)) {
        if (entry.path().extension() == ".txt") {
            std::string chemin = entry.path().string();
            std::cout << "\n=== Simulation : \"" << entry.path().filename() << "\" ===\n";

            Fourmiliere f;

            // Détection du format
            std::ifstream test(chemin);
            std::string premiereLigne;
            std::getline(test, premiereLigne);
            test.close();

            if (premiereLigne.find("f=") != std::string::npos) {
                chargerFourmiliereFormatAlternatif(chemin, f);
            } else {
                chargerFourmiliereFormatClassique(chemin, f);
            }

            // Vérifications avant de lancer la simulation
            if (!f.vestibule) {
                std::cout << "Erreur : salle Sv non trouvée dans " << chemin << "\n";
                continue;
            }

            if (!f.dortoir) {
                std::cout << "Erreur : salle Sd non trouvée dans " << chemin << "\n";
                continue;
            }

            if (f.fourmis.empty()) {
                std::cout << "Erreur : aucune fourmi trouvée dans " << chemin << "\n";
                continue;
            }

            std::cout << "+++ Simulation intelligente des deplacements +++\n";
            std::cout << "Vestibule : " << (f.vestibule ? f.vestibule->nom : "NON DÉFINI") << std::endl;
            std::cout << "Dortoir   : " << (f.dortoir ? f.dortoir->nom : "NON DÉFINI") << std::endl;
            std::cout << "Fourmis   : " << f.fourmis.size() << std::endl;

            std::cout << "+++ Simulation intelligente des deplacements +++\n";
            f.simulerDeplacementEtapes();

        }
    }

    return 0;
}
