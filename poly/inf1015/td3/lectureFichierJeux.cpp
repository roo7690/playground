// Fonctions pour lire le fichier binaire.
#include "lectureFichierJeux.hpp"
#include <fstream>
#include <cstdint>
#include "cppitertools/range.hpp"
#include <type_traits>

using namespace std;

using UInt8  = uint8_t;
using UInt16 = uint16_t;

#pragma region "Fonctions de lecture de base"
//TODO - Done: Remplacer lireUInt8 et lireUInt16 par une seule fonction générique qui permet les deux, mais permettre uniquement des types qui sont is_trivially_copyable_v (un trait de type).

template<typename T>
requires is_trivially_copyable_v<T>
T lire(istream &fichier)
{
	T valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

string lireString(istream& fichier)
{
	string texte;
	texte.resize(lire<UInt16>(fichier));
	fichier.read(reinterpret_cast<char*>(&texte[0]), streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}
#pragma endregion

pConcepteur chercherConcepteur(ListeJeux& listeJeux, const string& nom)
{
	//TODO - Done: Compléter la fonction (équivalent de trouverDesigner du TD2).

	for (unsigned i: range(listeJeux.size())) {
		auto pConcepteur = listeJeux[i].findConcepteur(
			[&](ListeConcepteurs::pItem pConcepteur)->bool {
				return pConcepteur->getNom() == nom;
			}
		);
		if (pConcepteur != nullptr) return pConcepteur;
	}

	return nullptr;
}

pConcepteur lireConcepteur(ListeJeux& lj, istream& f)
{
	string nom              = lireString(f);
	unsigned anneeNaissance = lire<UInt16>(f);
	string pays             = lireString(f);

	//TODO - Done: Compléter la fonction (équivalent de lireDesigner du TD2).

	auto pConcepteur = chercherConcepteur(lj, nom);
	if (pConcepteur != nullptr) return pConcepteur;

	auto concepteur = Concepteur({nom, anneeNaissance, pays});
	return make_shared<Concepteur>(concepteur);
}

pJeu lireJeu(istream& f, ListeJeux& lj)
{
	string titre          = lireString(f);
	unsigned anneeSortie  = lire<UInt16>(f);
	string developpeur    = lireString(f);
	unsigned nConcepteurs = lire<UInt8>(f);

	//TODO - Done: Compléter la fonction (équivalent de lireJeu du TD2).

	auto pJeu = lj.find(
		[&](ListeJeux::pItem pJeu)->bool {
			return pJeu->getTitre() == titre;
		}
	);
	if (pJeu != nullptr) return pJeu;

	auto jeu = Jeu({titre, anneeSortie, developpeur, ListeConcepteurs()});
	for (unsigned i: range(nConcepteurs)) {
		auto pConcepteur = lireConcepteur(lj, f);
		jeu.getConcepteurs().add(pConcepteur);
	}

	return make_shared<Jeu>(jeu);
}

ListeJeux creerListeJeux(const string& nomFichier)
{
	ifstream f(nomFichier, ios::binary);
	f.exceptions(ios::failbit);
	int nElements = lire<UInt16>(f);

	//string err = lire<string>(f);

	//TODO - Done: Compléter la fonction.

	ListeJeux listeJeux;
	for ([[maybe_unused]] int i : iter::range(nElements)) {
		auto pJeu = lireJeu(f, listeJeux);
		listeJeux.add(pJeu);
	}

	return listeJeux;
}
