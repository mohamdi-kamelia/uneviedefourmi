#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include <set>
#include <fstream>

class Salle {
public:
    std::string nom;
    int capacite;
    std::vector<Salle*> connexions;

    Salle(std::string nom, int capacite);
};

class Fourmi {
public:
    std::string id;
    std::vector<Salle*> chemin;
    int positionIndex = 0;

    Fourmi(std::string id);
};

class Fourmiliere {
public:
    std::unordered_map<std::string, Salle*> salles;
    std::vector<Fourmi> fourmis;
    Salle* vestibule = nullptr;
    Salle* dortoir = nullptr;

    void ajouterSalle(std::string nom, int capacite);
    void ajouterTunnel(std::string s1, std::string s2);
    void ajouterFourmi(std::string id);
    void afficherGraphe();

    void genererCheminsPourToutesLesFourmis();
    void simulerDeplacementEtapes();
    void exporterEtapeGraphviz(int etape, const std::unordered_map<std::string, std::string>& positions);
    std::vector<Salle*> cheminVersDortoir(Salle* depart);
};
