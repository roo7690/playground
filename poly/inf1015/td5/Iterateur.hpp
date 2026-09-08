#pragma once
#include "Noeud.hpp"
#include "gsl/gsl_assert"
template<typename T>
class Iterateur
{
	friend class ListeLiee<T>;
public:
	//TODO_Done: Constructeur(s).
	Iterateur(Noeud<T>* const noeud) : position_(noeud) {}
	Iterateur& operator=(Iterateur const&) = default;

	void avancer()
	{
		Expects(position_ != nullptr);
		//TODO_Done: changez la position de l'itérateur pour le noeud suivant
		position_ = position_->next_;
	}
	void reculer()
	{
		//NOTE: On ne demande pas de supporter de reculer à partir de l'itérateur end().
		Expects(position_ != nullptr);
		//TODO_Done: Changez la position de l'itérateur pour le noeud précédent
		position_ = position_->previous_;
	}
	
	T& operator*()
	{
		return position_->donnee_;
	}
	//TODO_Done: Ajouter ce qu'il manque pour que les boucles sur intervalles fonctionnent sur une ListeLiee.
	bool operator==(const Iterateur<T>& it) const = default;

	Iterateur<T>& operator++() {
		avancer();
		return *this;
	}
	Iterateur<T>& operator++(int) {
		avancer();
		return *this;
	}
	Iterateur<T>& operator+=(int n) {
		while (n-- > 0) avancer();
		return *this;
	}

	Iterateur<T>& begin() {
		return *this;
	}
	Iterateur<T> end() const {
		return Iterateur<T>((Noeud<T>*)nullptr);
	}

private:
	Noeud<T>* position_;
};
