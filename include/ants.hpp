#ifndef ANTS_HPP
#define ANTS_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

class Fourmi {
public:
    int id;
    std::string position;
    Fourmi(int id, std::string position);
};

class Salle {
public:
    std::string nom;
    int capacite;
    std::vector<std::string> connexions;

    Salle(std::string nom, int capacite = 1);
    void ajouterConnexion(std::string salle);
};

class Fourmiliere {
public:
    std::unordered_map<std::string, Salle> salles;
    std::vector<Fourmi> fourmis;
    std::string entree, sortie;

    Fourmiliere(std::string entree, std::string sortie);
    void ajouterSalle(std::string nom, int capacite = 1);
    void ajouterTunnel(std::string salle1, std::string salle2);
    std::vector<std::string> trouverChemin(std::string depart, std::string arrivee);
    void deplacerFourmis();
};

#endif
