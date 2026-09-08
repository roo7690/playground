#include "Jeu.hpp"
#include <iostream>
#include <fstream>
#include <span>
#include <cassert>
#include "cppitertools/range.hpp"
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"
#include "ListeDeveloppeurs.hpp"
#include "debogage_memoire.hpp"  // Ajout des numéros de ligne des "new" dans le rapport de fuites.  Doit être après les include du système, qui peuvent utiliser des "placement new" (non supporté par notre ajout de numéros de lignes).

using namespace std;
using namespace iter;

#pragma region "Fonctions de base pour vous aider"
typedef uint8_t UInt8;
typedef uint16_t UInt16;
UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read((char*)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}
#pragma endregion

span<Jeu*> spanListeJeux(const ListeJeux& liste)
{
	return span(liste.elements, liste.nElements);
}
span<Designer*> spanListeDesigners(const ListeDesigners& liste)
{
	return span(liste.elements, liste.nElements);
}

//TODO: Fonction qui cherche un designer par son nom dans une ListeJeux.  Devrait utiliser span.
Designer* trouverDesigner(const ListeJeux& listeJeux, string nom)
{
	for (const Jeu* j : spanListeJeux(listeJeux)) {
		// Normalement on voudrait retourner un pointeur const, mais cela nous
		// empêcherait d'affecter le pointeur retourné lors de l'appel de cette
		// fonction.
		for (Designer* d : spanListeDesigners(j->designers)) {
			if (d->nom == nom)
				return d;
		}
	}
	return nullptr;
}


Designer* lireDesigner(istream& fichier, ListeJeux& listeJeux)
{
	Designer designer = {};
	designer.nom = lireString(fichier);
	designer.anneeNaissance = lireUint16(fichier);
	designer.pays = lireString(fichier);

	//TODO: Ajouter en mémoire le designer lu. Il faut revoyer le pointeur créé.
	// TIP: Afficher un message lorsque l'allocation du designer est réussie pour aider au débogage.
	// Vous pouvez enlever l'affichage une fois que le tout fonctionne.
	Designer* designerExistant = trouverDesigner(listeJeux, designer.nom);
	if (designerExistant != nullptr)
		return designerExistant;

	//cout << designer.nom << endl;  //TODO: Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.
	cout << "\033[92m" << "Allocation en mémoire du designer " << designer.nom
				<< "\033[0m" << endl;
	return new Designer(designer); //TODO: Retourner le pointeur vers le designer crée.
}

//TODO: Fonction qui change la taille du tableau de jeux de ListeJeux.
void changerTailleListeJeux(ListeJeux& liste, unsigned nouvelleCapacite)
{
	assert(nouvelleCapacite >= liste.nElements); // On ne demande pas de supporter les réductions de nombre d'éléments.
	Jeu** nouvelleListeJeux = new Jeu* [nouvelleCapacite];
	// Pas nécessaire de tester si liste.elements est nullptr puisque si c'est le cas, nElements est nécessairement 0.
	for(int i : iter::range(liste.nElements))
		nouvelleListeJeux[i] = liste.elements[i];
	delete[] liste.elements;

	liste.elements = nouvelleListeJeux;
	liste.capacite = nouvelleCapacite;
}

//TODO: Fonction pour ajouter un Jeu à ListeJeux.
void ajouterJeu(ListeJeux& liste, Jeu* jeu)
{
	if(liste.nElements == liste.capacite)
		changerTailleListeJeux(liste, max(1U, liste.capacite * 2));
	liste.elements[liste.nElements++] = jeu;
}

//TODO: Fonction qui enlève un jeu de ListeJeux.
void enleverJeu(ListeJeux& liste, const Jeu* jeu)
{
	for (Jeu*& elem : spanListeJeux(liste)) {
		if (elem == jeu) {
			elem = liste.elements[--liste.nElements];
			return;
		}
	}
}

Jeu* lireJeu(istream& fichier, ListeJeux& listeJeux)
{
	Jeu jeu = {};
	jeu.titre = lireString(fichier);
	jeu.anneeSortie = lireUint16(fichier);
	jeu.developpeur = lireString(fichier);
	jeu.designers.nElements = lireUint8(fichier);

	//TODO: Ajouter en mémoire le jeu lu. Il faut revoyer le pointeur créé.
	// TIP: Afficher un message lorsque l'allocation du jeu est réussie pour aider au débogage.
	// Vous pouvez enlever l'affichage une fois que le tout fonctionne.
	Jeu* ptrJeu = new Jeu(jeu);  // Ou allouer directement au début plutôt qu'en faire une copie ici.
	cout << "\033[96m" << "Allocation en mémoire du jeu " << jeu.titre
			  << "\033[0m" << endl;

	ptrJeu->designers.elements = new Designer* [ptrJeu->designers.nElements];  // On n'a pas demandé de faire une réallocation dynamique pour les designers.
	for (Designer*& d : spanListeDesigners(ptrJeu->designers)) {
		d = lireDesigner(fichier, listeJeux);  //TODO: Mettre le designer dans la liste des designer du jeu.
		ajouterJeu(d->listeJeuxParticipes, ptrJeu); //TODO: Ajouter le jeu à la liste des jeux auquel a participé le designer.
	}
	return ptrJeu; //TODO: Retourner le pointeur vers le nouveau jeu.
}

ListeJeux creerListeJeux(const string& nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	int nElements = lireUint16(fichier);
	ListeJeux listeJeux = {};
	for ([[maybe_unused]] int n : iter::range(nElements))
	{
		ajouterJeu(listeJeux, lireJeu(fichier, listeJeux)); //TODO: Ajouter le jeu à la ListeJeux.
	}

	return listeJeux; //TODO: Renvoyer la ListeJeux.
}


void detruireDesigner(Designer* d)
{
	cout << "\033[91m" << "Destruction du designer " << d->nom << "\033[0m"
			  << endl;
	delete[] d->listeJeuxParticipes.elements;
	delete d;
}

bool encorePresentDansUnJeu(const Designer* d)
{
	return d->listeJeuxParticipes.nElements != 0;
}

//TODO: Fonction pour détruire un jeu (libération de mémoire allouée).
// TIP: Afficher un message lorsque le jeu est détruit pour aider au débogage.
// Vous pouvez enlever l'affichage une fois que le tout fonctionne.
void detruireJeu(Jeu* jeu)
{
	for (Designer* d : spanListeDesigners(jeu->designers)) {
		enleverJeu(d->listeJeuxParticipes, jeu);
		if (!encorePresentDansUnJeu(d))
			detruireDesigner(d);
	}
	cout << "\033[31m" << "Destruction du jeu " << jeu->titre << "\033[0m"
			  << endl;
	delete[] jeu->designers.elements;
	delete jeu;
}


//TODO: Fonction pour détruire une ListeJeux et tous ses jeux.
void detruireListeJeux(ListeJeux& liste)
{
	for(Jeu* j : spanListeJeux(liste))
		detruireJeu(j);
	delete[] liste.elements;
}

//TODO: Fonction pour afficher les infos d'un designer.
void afficherDesigner(const Designer& d)
{
	cout << "\t" << d.nom << ", " << d.anneeNaissance << ", " << d.pays
	     << endl;
}

//TODO: Fonction pour afficher les infos d'un jeu ainsi que ses designers.
void afficherJeu(const Jeu& j)
{
	cout << "Titre : " << "\033[94m" << j.titre << "\033[0m" << endl;
	cout << "Parution : " << "\033[94m" << j.anneeSortie << "\033[0m"
			  << endl;
	cout << "Développeur :  " << "\033[94m" << j.developpeur << "\033[0m"
			  << endl;
	cout << "Designers du jeu :" << "\033[94m" << endl;
	for(const Designer* d : spanListeDesigners(j.designers))
		afficherDesigner(*d);
	cout << "\033[0m";
}


//TODO: Fonction pour afficher tous les jeux de ListeJeux, séparés par un ligne.
// Votre ligne de séparation doit être différent de celle utilisée dans le main.
void afficherListeJeux(const ListeJeux& listeJeux)
{
	static const string ligneSeparation = "\n\033[95m"
	"══════════════════════════════════════════════════════════════════════════"
	"\033[0m\n";
	cout << ligneSeparation << endl;
	for(const Jeu* j : spanListeJeux(listeJeux))
	{
		afficherJeu(*j);
		cout << ligneSeparation << endl;
	}
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
#pragma endregion

	//int* fuite = new int;  // Pour vérifier que la détection de fuites fonctionne; un message devrait dire qu'il y a une fuite à cette ligne.

	ListeJeux lj = creerListeJeux("jeux.bin"); //TODO: Appeler correctement votre fonction de création de la liste de jeux.

	static const string ligneSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";
	cout << ligneSeparation << endl;
	cout << "Premier jeu de la liste :" << endl;
	//TODO: Afficher le premier jeu de la liste (en utilisant la fonction).  Devrait être Chrono Trigger.
	afficherJeu(*lj.elements[0]);
	cout << ligneSeparation << endl;

	//TODO: Appel à votre fonction d'affichage de votre liste de jeux.
	afficherListeJeux(lj);

	//TODO: Faire les appels à toutes vos fonctions/méthodes pour voir qu'elles fonctionnent et avoir 0% de lignes non exécutées dans le programme (aucune ligne rouge dans la couverture de code; c'est normal que les lignes de "new" et "delete" soient jaunes).  Vous avez aussi le droit d'effacer les lignes du programmes qui ne sont pas exécutée, si finalement vous pensez qu'elle ne sont pas utiles.

	// PARTIE 2
	ListeDeveloppeurs ld;
	// Création des développeurs externes à la liste des développeur
	Developpeur* nintendo = new Developpeur("Nintendo");
	Developpeur* square = new Developpeur("Square");
	Developpeur* bidon = new Developpeur("Bidon");
	Developpeur* konami = new Developpeur("Konami");
	// On ajoute les jeux respectifs de ListeJeux développé par le développeur
	nintendo->ajouterJeux(lj);
	square->ajouterJeux(lj);
	konami->ajouterJeux(lj);
	// On ajoute les développeurs à la ListeDeveloppeur car ils sont externes
	ld.ajouter(nintendo);
	ld.ajouter(square);
	ld.ajouter(konami);
	ld.ajouter(bidon);
	// On affiche la liste des développeurs, leurs jeux sont aussi affichés; Bidon ne devrait avoir aucun jeu.
	ld.afficher();

	cout << endl << "On retire " << konami->getNom() << endl;
	ld.retirer(konami); // Retire sans détruire.
	ld.afficher();
	cout << "Il existe encore: " << konami->getNom() << endl;

	delete nintendo;
	delete square;
	delete konami;
	delete bidon;

	//TODO: Détruire tout avant de terminer le programme.  Devrait afficher "Aucune fuite detectee." a la sortie du programme; il affichera "Fuite detectee:" avec la liste des blocs, s'il manque des delete.
	detruireListeJeux(lj);
}
