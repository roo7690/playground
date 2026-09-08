#pragma once
#include <string>
#include <tuple>
#include "Liste.hpp"

using namespace std;

class Concepteur
{
public:
	//TODO - Done: Un constructeur par défaut et un constructeur paramétré.
	Concepteur(): nom_(""), anneeNaissance_(0), pays_("") {}
	Concepteur(tuple<string, int, string> params);

	const std::string& getNom() const     { return nom_; }
	void setNom(std::string nom)          { nom_ = move(nom); }
	int getAnneeNaissance() const         { return anneeNaissance_; }
	void setAnneeNaissance(int annee)     { anneeNaissance_ = annee; }
	const std::string& getPays() const    { return pays_; }
	void setPays(std::string pays)        { pays_ = move(pays); }

private:
	std::string nom_;
	int anneeNaissance_;
	std::string pays_;
};

using ListeConcepteurs = Liste<Concepteur>;