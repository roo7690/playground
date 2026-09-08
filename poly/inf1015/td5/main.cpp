/*
	Auteur :
		* Roosevelt Sonfack Ngoune - 2464064
		* Max Bleriot Mba Fossi - 2417938
	Date : 01/04/2026
*/

#include "Personnage.hpp"
#include "Heros.hpp"
#include "Vilain.hpp"
#include "VilainHeros.hpp"
#include "ListeLiee.hpp"
#include <fstream>
#include <vector>
#include <functional>
#include "cppitertools/range.hpp"
#include "bibliotheque_cours.hpp"
#include <cassert>
#include <map>

using namespace std;
using namespace iter;

using UInt8  = uint8_t;
using UInt16 = uint16_t;

#define VIEW_HEROS_AND_VILAINS 0

UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read(reinterpret_cast<char*>(&texte[0]), streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}

template <typename T>
vector<T> lireFichier(istream& fichier)
{
	vector<T> elements;
	for ([[maybe_unused]] int i : range(lireUint16(fichier)))
		elements.push_back(T(fichier));
	return elements;
}

ifstream ouvrirLectureFichierBinaire(const string& nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	return fichier;
}

// Permet d'avoir une référence non-const à un objet temporaire.
template <typename T> T& temporaireModifiable(T&& objet) { return objet; }

template <typename T>
vector<T> lireFichier(const string& nomFichier)
{
	return lireFichier<T>(temporaireModifiable(
		ouvrirLectureFichierBinaire(nomFichier)));
}

template <typename T>
Iterateur<T> trouverParNom(ListeLiee<T>& liste, const string& nom)
{
	Iterateur<T> fin = liste.end();
	for (Iterateur<T> pos = liste.begin(); pos != fin; pos.avancer()) {
		if ((*pos).getNom() == nom)
			return pos;
	}
	return fin;
}

int main()
{
	#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
	#pragma endregion
	
	// Trait de separation
	static const string trait =
		"═════════════════════════════════════════════════════════════════════════";

	static const string separateurSections = "\033[95m" + trait + "\033[0m\n";
	static const string separateurElements = "\033[33m" + trait + "\033[0m\n";

	//{ Solutionnaire du TD4:
	vector<Heros> heros = lireFichier<Heros>("heros.bin");
	vector<Vilain> vilains = lireFichier<Vilain>("vilains.bin");
	vector<unique_ptr<Personnage>> peronnages;  // Doit être des pointeurs pour le polymorphisme, l'énoncé ne force pas les unique_ptr.

	#if VIEW_HEROS_AND_VILAINS //TODO_Done: Vous n'avez pas à conserver ces affichages pour le TD5, ils sont pour le solutionnaire du TD4:
	cout << separateurSections << "Heros:" << endl;
	for (auto& h : heros) {
		cout << separateurElements;
		h.changerCouleur(cout, 0);
		h.afficher(cout);
	}

	cout << separateurSections << "Vilains:" << endl;
	for (auto& v : vilains) {
		cout << separateurElements;
		v.changerCouleur(cout, 0);
		v.afficher(cout);
	}

	for (auto& h : heros)
		peronnages.push_back(make_unique<Heros>(h));

	for (auto& v : vilains)
		peronnages.push_back(make_unique<Vilain>(v));

	peronnages.push_back(make_unique<VilainHeros>(vilains[1], heros[2]));

	cout << separateurSections << "Personnages:" << endl;
	for (auto& p : peronnages) {
		cout << separateurElements;
		p->changerCouleur(cout, 0);
		p->afficher(cout);
	}
	cout << separateurSections << "Un autre vilain heros (exemple de l'énoncé du TD):" << endl;
	VilainHeros kefkaCrono(vilains[2], heros[0]);
	kefkaCrono.changerCouleur(cout,1);
	kefkaCrono.afficher(cout);
	#endif
	//}

	//TODO_Done: Transférez les héros du vecteur heros dans une ListeLiee.
	ListeLiee<Heros> listeHeros;
	for (Heros& hero: heros)
		listeHeros.push_back(hero);

	//TODO_Done: Créez un itérateur sur la liste liée à la position du héros Alucard
	// Servez-vous de la fonction trouverParNom définie plus haut
	Iterateur<Heros> iter = trouverParNom(listeHeros, "Alucard");

	//TODO_Done: Servez-vous de l'itérateur créé précédemment pour trouver l'héroine Aya Brea,
	// en sachant qu'elle se trouve plus loin dans la liste.
	while ((*iter).getNom() != "Aya Brea") iter.avancer();

	//TODO_Done: Ajouter un hero bidon à la liste avant Aya Brea en vous servant de l'itérateur.
	listeHeros.insert(iter, Heros("Deku", "BattleRoyale", "AllianceOfVillains"));
	
	//TODO_Done: Assurez-vous que la taille de la liste est correcte après l'ajout.
	assert(listeHeros.size() == heros.size() + 1);

	//TODO_Done: Reculez votre itérateur jusqu'au héros Mario et effacez-le en utilisant l'itérateur, puis affichez le héros suivant dans la liste (devrait êter "Naked Snake/John").
	while((*iter).getNom() != "Mario") iter.reculer();
	listeHeros.erase(iter);
	
	//TODO_Done: Assurez-vous que la taille de la liste est correcte après le retrait.
	assert(listeHeros.size() == heros.size());

	//TODO_Done: Effacez le premier élément de la liste.
	listeHeros.erase(listeHeros.begin());

	//TODO_Done: Affichez votre liste de héros en utilisant un itérateur. La liste débute
	// avec le héros Randi et n'a pas Mario.
	// Servez-vous des methodes begin et end de la liste...
	for (Iterateur<Heros> it = listeHeros.begin(); it != listeHeros.end(); it++) {
		(*it).afficher(cout);
	}

	//TODO_Done: Refaite le même affichage mais en utilisant une simple boucle "for" sur intervalle.
	cout << "Meme affichage: " << separateurSections << endl;
	for (Heros hero: listeHeros.begin())
		hero.afficher(cout);

	//TODO_Done: Utilisez un conteneur pour avoir les héros en ordre alphabétique (voir point 2 de l'énoncé).
	map<string, Heros> herosOrdonne;
	for (Heros hero: listeHeros.begin())
		herosOrdonne[hero.getNom()] = hero;

	//2.2 La complexite en moyenne de cette recherche est O(log n) car la recherche s'effectue sur un arbre equilibre.
	//2.2 A chaque etape, on elimine la moitie des possibilites.
	Heros link = herosOrdonne.find("Link")->second;
	cout << "Link trouve dans le map: " << separateurSections << endl;
	link.afficher(cout);

	//2.3 Le conteneur qui permet la recherche la plus rapide entre listeHeros et herosOrdonne est evidemment herosOrdonne.
	//2.3 Car la recherche dans listeHeros est O(n) (lineaire), il faut parcourir toutes la liste jusque l'element recherche.
	//2.3 Alors que la recherche dans herosOrdonne est O(log n) (logarithmique), il faut parcourir au plus log2(n) elements pour trouver l'element recherche.

	//TODO_Done: Assurez-vous de n'avoir aucune ligne non couverte dans les classes pour la liste liée.  Il peut y avoir des lignes non couvertes dans les personnages...

}
