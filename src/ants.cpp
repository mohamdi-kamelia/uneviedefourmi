#include "ants.hpp"
#include <map>
#include <sstream>

Salle::Salle(std::string nom, int capacite) : nom(nom), capacite(capacite) {}
Fourmi::Fourmi(std::string id) : id(id) {}

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
    Fourmi f(id);
    f.chemin = cheminVersDortoir(vestibule);
    fourmis.push_back(f);
}

void Fourmiliere::afficherGraphe() {
    std::cout << "Graphe de la fourmilière :\n";
    for (auto& [nom, salle] : salles) {
        std::cout << salle->nom << " -> ";
        for (auto& adj : salle->connexions) {
            std::cout << adj->nom << " ";
        }
        std::cout << "\n";
    }
}

std::vector<Salle*> Fourmiliere::cheminVersDortoir(Salle* depart) {
    std::unordered_map<Salle*, Salle*> parent;
    std::queue<Salle*> q;
    std::set<Salle*> visited;

    q.push(depart);
    visited.insert(depart);

    while (!q.empty()) {
        Salle* current = q.front(); q.pop();
        if (current == dortoir) break;
        for (Salle* voisin : current->connexions) {
            if (!visited.count(voisin)) {
                visited.insert(voisin);
                parent[voisin] = current;
                q.push(voisin);
            }
        }
    }

    std::vector<Salle*> chemin;
    Salle* cur = dortoir;
    while (cur != depart) {
        chemin.insert(chemin.begin(), cur);
        cur = parent[cur];
    }
    chemin.insert(chemin.begin(), depart);
    return chemin;
}

void Fourmiliere::simulerDeplacementEtapes() {
    std::cout << "\n+++ Simulation intelligente des deplacements +++\n";
    int etape = 1;
    std::unordered_map<std::string, std::string> positionFourmis;

    for (auto& f : fourmis) {
        positionFourmis[f.id] = vestibule->nom;
    }

    while (true) {
        bool mouvement = false;
        std::set<std::string> occupation;
        for (auto& f : fourmis) {
            if (f.positionIndex < f.chemin.size() - 1) {
                std::string prochaine = f.chemin[f.positionIndex + 1]->nom;
                if (occupation.count(prochaine) == 0 || prochaine == dortoir->nom) {
                    occupation.insert(prochaine);
                    f.positionIndex++;
                    positionFourmis[f.id] = prochaine;
                    mouvement = true;
                }
            }
        }

        std::cout << "+++ E " << etape << " +++\n";
        for (auto& [id, pos] : positionFourmis) {
            std::cout << id << " est dans " << pos << "\n";
        }

        exporterEtapeGraphviz(etape, positionFourmis);

        if (!mouvement) break;
        etape++;
    }

    std::cout << "\nToutes les fourmis sont arrivées au dortoir.\n";
}

void Fourmiliere::exporterEtapeGraphviz(int etape, const std::unordered_map<std::string, std::string>& positions) {
    std::ofstream fichier("output/etape" + std::to_string(etape) + ".dot");
    fichier << "digraph Fourmiliere {\n";

    for (auto& [nom, salle] : salles) {
        fichier << "  " << nom << " [label=\"" << nom;
        for (auto& [id, pos] : positions) {
            if (pos == nom) fichier << "\\n" << id;
        }
        fichier << "\"];\n";
        for (Salle* conn : salle->connexions) {
            if (nom < conn->nom) // éviter doublons
                fichier << "  " << nom << " -> " << conn->nom << ";\n";
        }
    }

    fichier << "}\n";
    fichier.close();
}
