#include "include/ants.hpp"

int main() {
    // Création de la fourmilière
    Fourmiliere fourmiliere("S_v", "S_d");

    // Ajout des salles
    fourmiliere.ajouterSalle("S_v"); // Vestibule
    fourmiliere.ajouterSalle("S_d"); // Dortoir
    fourmiliere.ajouterSalle("S1");
    fourmiliere.ajouterSalle("S2");

    // Ajout des tunnels
    fourmiliere.ajouterTunnel("S_v", "S1");
    fourmiliere.ajouterTunnel("S_v", "S2");
    fourmiliere.ajouterTunnel("S1", "S_d");
    fourmiliere.ajouterTunnel("S2", "S_d");

    // Ajout des fourmis
    for (int i = 1; i <= 3; i++) {
        fourmiliere.fourmis.push_back(Fourmi(i, "S_v"));
    }

    // Déplacer les fourmis
    std::cout << "Déplacement des fourmis :\n";
    fourmiliere.deplacerFourmis();

    return 0;
}
