#ifndef ANTS_HPP
#define ANTS_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>

class Salle {
public:
    std::string nom;
    int capacite;
    std::vector<Salle*> connexions;
    Salle(std::string nom, int capacite = 1);
};

class Fourmi {
public:
    std::string id;
    Salle* position;
    Fourmi(std::string id, Salle* position);
};

class Fourmiliere {
public:
    Salle* vestibule;
    Salle* dortoir;
    std::map<std::string, Salle*> salles;
    std::vector<Fourmi> fourmis;

    void ajouterSalle(std::string nom, int capacite = 1);
    void ajouterTunnel(std::string s1, std::string s2);
    void ajouterFourmi(std::string id);
    void afficherGraphe();
    void simulerDeplacement();
};

#endif
