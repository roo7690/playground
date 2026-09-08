#pragma once
#include "gsl/span"
#include <memory>
#include "cppitertools/range.hpp"
#include <tuple>

using namespace std;
using namespace gsl;
using namespace iter;

//TODO - Done: Rendre la liste générique.
template<typename T>
class Liste
{
public:
	using pItem = shared_ptr<T>;

	//TODO - Done: Constructeurs et surcharges d'opérateurs
	Liste() : nElements_(0), capacite_(0), items(nullptr) {}
	Liste(span<pItem const> items) :
		Liste(parser(items)) {} // initializer list delegue a la methode private List
	//copie list (pas de copie des elements ou items)
	Liste(Liste const &list);

	//get item from list
	T& operator[](unsigned index) { return *this->items[index]; }
	pItem& operator[](unsigned *index) { return this->items[*index]; }

	//TODO - Done: Méthode pour ajouter un élément à la liste
	void add(pItem item);

	// Pour size, on utilise le même nom que les accesseurs de la bibliothèque standard, qui permet d'utiliser certaines fonctions de la bibliotheque sur cette classe.
	unsigned size() const         { return nElements_; }
	unsigned getCapacite() const  { return capacite_; }

	//TODO - Done: Méthode pour changer la capacité de la liste
	void setCapacite(unsigned size);

	//TODO - Done: Méthode pour trouver un élément selon un critère (lambda).
	pItem find(function<bool(pItem)> fn);

private:
	unsigned nElements_;
	unsigned capacite_;
	//TODO - Done: Attribut contenant les éléments de la liste.
	unique_ptr<pItem[]> items;

	// constructor

	tuple<unique_ptr<pItem[]>, unsigned, unsigned>
	parser(span<pItem const> items);

	Liste(tuple<unique_ptr<pItem[]>, unsigned, unsigned> items);
};

// constructor

template<typename T>
Liste<T>::Liste(Liste const &list) :
	nElements_(list.nElements_),
	capacite_(list.capacite_),
	items(make_unique<pItem[]>(list.capacite_)) 
{
	for(unsigned i: range(list.nElements_)) {
		this->items[i] = list.items[i];
	}
};

template<typename T>
Liste<T>::Liste(tuple<unique_ptr<pItem[]>, unsigned, unsigned> items) :
	nElements_(get<1>(items)),
  capacite_(get<2>(items)),
  items(move(get<0>(items)))
  {};

template<typename T>
tuple<unique_ptr<typename Liste<T>::pItem[]>, unsigned, unsigned>
Liste<T>::parser(span<pItem const> items)
{
  unsigned capacite = items.size();
  unsigned nElements = 0;
  unique_ptr<pItem[]> list = make_unique<pItem[]>(capacite);

  for (pItem pItem: items) {
    if (pItem == nullptr) break;
    list[nElements] = pItem;
    nElements += 1;
  }

  return { move(list), nElements, capacite };
}

// set method

template<typename T>
void Liste<T>::add(pItem item)
{
	for (unsigned i: range(this->nElements_)) {
		if (item == this->items[i]) return;
	}

	if (this->nElements_ == this->capacite_) {
		this->setCapacite((this->capacite_ ? this->capacite_ : 1) * 2);
	}

	this->items[this->nElements_] = item;
	this->nElements_ += 1;
}

template<typename T>
void Liste<T>::setCapacite(unsigned size)
{
	if (size == this->capacite_) return;

	unique_ptr<pItem[]> list = size != 0 ? make_unique<pItem[]>(size) : nullptr;
	unsigned nElements = this->nElements_ < size ? this->nElements_ : size;

	for (unsigned i: range(nElements)) {
		list[i] = this->items[i];
	}

	this->items = move(list);
	this->capacite_ = size;
	this->nElements_ = nElements;
}

// filter method

template<typename T>
Liste<T>::pItem
Liste<T>::find(function<bool(pItem)> fn)
{
	for (unsigned i: range(this->nElements_)) {
		if (fn(this->items[i]) == true) return this->items[i];
	}
	return nullptr;
}