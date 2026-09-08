#pragma once
#include "Iterateur.hpp"
#include "gsl/gsl_assert"
template<typename T> class Iterateur;
template<typename T>
class ListeLiee
{
	friend class Iterateur<T>;
public:
	using iterator = Iterateur<T>;  // Définit un alias au type, pour que ListeLiee<T>::iterator corresponde au type de son itérateur.
	using noeud = Noeud<T>;

	//TODO_Done: La construction par défaut doit créer une liste vide valide.
	ListeLiee() : tete_(nullptr), queue_(nullptr), taille_(0) {}
	~ListeLiee()
	{
		//TODO_Done: Enlever la tête à répétition jusqu'à ce qu'il ne reste aucun élément.
		// Pour enlever la tête, 
		// 1. La tête doit devenir le suivant de la tête actuelle.
		// 2. Ne pas oublier de désallouer le noeud de l'ancienne tête (si pas fait automatiquement).
		
		// Implementation de Noeud -> si un Noeud est désalloué, il désalloue automatiquement son suivant, et ainsi de suite jusqu'à la fin de la liste.
		delete tete_;
	}

	bool estVide() const  { return taille_ == 0; }
	unsigned size() const { return taille_; }
	//NOTE: to_address (C++20) permet que ce même code fonctionne que vous utilisiez des pointeurs bruts ou intelligents (ça prend le pointeur brut associé au pointeur intelligent, s'il est intelligent).
	iterator begin()  { return {to_address(tete_)}; }
	iterator end()    { return {to_address(queue_->next_)}; }

	// Ajoute à la fin de la liste.
	void push_back(const T& item)
	{
		//TODO_Done: Vous devez créer un nouveau noeud en mémoire.
		noeud* newNode = new noeud(item);
		//TODO_Done: Si la liste était vide, ce nouveau noeud est la tête et la queue;
		// autrement, ajustez la queue et pointeur(s) adjacent(s) en conséquence.
		if (estVide()) {
			tete_ = newNode;
			queue_ = newNode;
		}
		else {
			queue_->next_ = newNode;
			newNode->previous_ = queue_;
			queue_ = newNode;
		}
		taille_++;
	}

	// Insère avant la position de l'itérateur.
	iterator insert(iterator it, const T& item)
	{
		//NOTE: Pour simplifier, vous n'avez pas à supporter l'insertion à la fin (avant "past the end"),
		// ni l'insertion au début (avant la tête), dans cette méthode.
		//TODO_Done:
		// 1. Créez un nouveau noeud initialisé avec item.
		noeud* node = new noeud(item);
		noeud* before = it.position_->previous_;
		// 2. Modifiez les attributs suivant_ et precedent_ du nouveau noeud
		//    afin que le nouveau noeud soit lié au noeud précédent et suivant
		//    à l'endroit où il est inséré selon notre itérateur.
		node->previous_ = before;
		node->next_ = it.position_;
		// 3. Modifiez l'attribut precedent_ du noeud après la position d'insertion
		//    (l'itérateur) afin qu'il pointe vers le noeud créé.
		it.position_->previous_ = node;
		// 4. Modifiez l'attribut suivant_ du noeud avant la position d'insertion
		//    (précédent de l'itérateur) afin qu'il point vers le noeud créé.
		before->next_ = node;
		// 5. Incrémentez la taille de la liste.
		taille_++;
		// 6. Retournez un nouvel itérateur initialisé au nouveau noeud.
		return iterator(node);
	}

	// Enlève l'élément à la position it et retourne un itérateur vers le suivant.
	iterator erase(iterator it)
	{
		//TODO_Done: Enlever l'élément à la position de l'itérateur.
		//  1. Le pointeur vers le Noeud à effacer est celui dans l'itérateur.
		noeud* toDelete = it.position_;
		noeud* before = toDelete->previous_;
		noeud* after = toDelete->next_;
		//  2. Modifiez l'attribut suivant_ du noeud précédent pour que celui-ci
		//     pointe vers le noeud suivant la position de l'itérateur (voir 1.).
		if (before) before->next_ = after;
		else tete_ = after;
		//  3. Modifiez l'attribut precedent_ du noeud suivant la position de
		//     l'itérateur pour que celui-ci pointe vers le noeud précédent
		//     de la position de l'itérateur (voir 1.).
		if (after) after->previous_ = before;
		else queue_ = before;
		//  4. Désallouez le Noeud à effacer (voir 1.).
		toDelete->next_ = nullptr; // Pour éviter que le destructeur de Noeud désalloue les suivants.
		delete toDelete;
		//  5. Décrémentez la taille de la liste
		taille_--;
		//  6. Retournez un itérateur vers le suivant du Noeud effacé.
		return iterator(after);

		//TODO_Done: On veut supporter d'enlever le premier élément de la liste,
		//  donc en 2. il se peut qu'il n'y ait pas de précédent et alors c'est
		//  la tête de liste qu'il faut ajuster.
		//NOTE: On ne demande pas de supporter d'effacer le dernier élément (c'est similaire au cas pour enlever le premier).
	}

private:
	gsl::owner<Noeud<T>*> tete_;  //NOTE: Vous pouvez changer le type si vous voulez.
	Noeud<T>* queue_;
	unsigned taille_;
};
