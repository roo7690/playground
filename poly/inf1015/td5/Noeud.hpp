#pragma once
#include <gsl/pointers>
template<typename T> class ListeLiee;
template<typename T> class Iterateur;

template<typename T>
class Noeud
{
	friend class ListeLiee<T>;
	friend class Iterateur<T>;
public:
	//TODO_Done: Constructeur(s).
	Noeud(const T& value) : donnee_(value), next_(nullptr), previous_(nullptr) {}
	~Noeud() { delete next_; }

private:
	//TODO_Done: Attributs d'un noeud.
	T donnee_;
	gsl::owner<Noeud<T>*> next_;
	Noeud<T>* previous_;
};
