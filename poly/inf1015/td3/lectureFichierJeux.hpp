// Fonctions pour lire le fichier binaire.
#pragma once
#include "Jeu.hpp"
#include "Concepteur.hpp"
#include <iostream>

using pConcepteur = shared_ptr<Concepteur>;
using pJeu = shared_ptr<Jeu>;

pConcepteur chercherConcepteur(ListeJeux& listeJeux, const std::string& nom);
pConcepteur lireConcepteur(ListeJeux& lj, std::istream& f);
pJeu lireJeu(std::istream& f, ListeJeux& lj);
ListeJeux creerListeJeux(const std::string& nomFichier);
