#pragma once
#include <string>
#include "Liste.hpp"
#include "Concepteur.hpp"

using namespace std;

class Jeu
{
public:
	//TODO - Done: un constructeur par défaut et un constructeur paramétré.
	Jeu(): titre_(""), anneeSortie_(0), developpeur_(""), concepteurs_(ListeConcepteurs()) {}
	Jeu(tuple<string, unsigned, string, ListeConcepteurs> params);

	const std::string& getTitre() const     { return titre_; }
	void setTitre(std::string titre)        { titre_ = move(titre); }
	unsigned getAnneeSortie() const         { return anneeSortie_; }
	void setAnneeSortie(unsigned annee)     { anneeSortie_ = annee; }
	const std::string& getDeveloppeur() const { return developpeur_; }
	void setDeveloppeur(std::string developpeur) { developpeur_ = move(developpeur); }

	//TODO - Done: Pouvoir accéder à la liste de concepteurs.
	ListeConcepteurs& getConcepteurs() { return concepteurs_; }
	ListeConcepteurs::pItem& getConcepteur(unsigned index) { return concepteurs_[&index]; }

	//TODO - Done: Votre méthode pour trouver un concepteur selon un critère donné par une lambda, en utilisant la méthode de Liste.
	ListeConcepteurs::pItem
	findConcepteur(function<bool(ListeConcepteurs::pItem)> fn) { return concepteurs_.find(fn); }

private:
	std::string titre_;
	unsigned anneeSortie_;
	std::string developpeur_;
	//TODO - Done: Attribut de la liste des concepteurs du jeu
	ListeConcepteurs concepteurs_;
};

using ListeJeux = Liste<Jeu>;  //TODO - Done: Remplacer cette définition (qui est ici juste pour que le code fourni compile) pour que ListeJeux soit une Liste<Jeu> .
