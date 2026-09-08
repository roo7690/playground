#include <iostream>
#include <fstream>
#include "Liste.hpp"
#include "Concepteur.hpp"
#include "Jeu.hpp"
#include "lectureFichierJeux.hpp"
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"

using namespace std;

//TODO - Done: Vos surcharges d'opérateur <<
ostream& operator<<(ostream& os, ListeConcepteurs& lc)
{
	for (unsigned i: range(lc.size())) {
		os << "\t" << lc[i].getNom() << ", " << lc[i].getAnneeNaissance()
			<< ", " << lc[i].getPays() << endl;
	}
	return os;
}

ostream& operator<<(ostream& os, Jeu& jeu) {
	os << "Titre : " << jeu.getTitre() << endl;
	os << "Parution : " << jeu.getAnneeSortie() << endl;
	os << "Développeur :  " << jeu.getDeveloppeur() << endl;
	os << "Concepteurs du jeu :" << endl;
	os << jeu.getConcepteurs() << endl;
	return os;
}

ostream& operator<<(ostream& os, ListeJeux& lj)
{
	for (unsigned i: range(lj.size())) {
		os << lj[i];
	}
	return os;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi(); 
	#pragma endregion
	
	ListeJeux listeJeux = creerListeJeux("jeux.bin");
	static const string ligneSeparation = "\n\033[92m"
		"══════════════════════════════════════════════════════════════════════════"
		"\033[0m\n";

	//TODO - Done: L'affichage de listeJeux et l'écriture dans le fichier devraient fonctionner.
	cout << listeJeux << ligneSeparation;

	ofstream file("build/liste_jeux.txt");
	file << listeJeux << ligneSeparation;

	//TODO - Done: Compléter le main avec les tests demandés.
	//TODO - Done: S'assurer qu'aucune ligne de code est non couverte.
	//NOTE: Il n'est pas nécessaire de couvrir les getters/setters simples fournis; il faut tester si vous en ajoutez ou les modifiez.
	//NOTE: Pour Liste, qui est générique, on demande de couvrir uniquement pour Liste<Jeu>, pas pour tous les types.

	Jeu copieJeu = listeJeux[(unsigned)2];
	copieJeu.getConcepteur(1) = listeJeux[(unsigned)0].getConcepteur(3);

	cout << "Jeu a l'indice 2" << endl;
	cout << listeJeux[(unsigned)2];
	cout << "Copie modifie" << endl;
	cout << copieJeu;
	cout << "Meme adresse pour le premier concepteur : "
		<< ((listeJeux[(unsigned)2].getConcepteur(0) == copieJeu.getConcepteur(0)) ? "true" : "false")
		<< " ( " << listeJeux[(unsigned)2].getConcepteur(0) << " , " << copieJeu.getConcepteur(0) << " )"
		<< endl;
}