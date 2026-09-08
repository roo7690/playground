#include "Jeu.hpp"

// Constructeur parametre
Jeu::Jeu(tuple<string, unsigned, string, ListeConcepteurs> params) :
	titre_(get<0>(params)),
	anneeSortie_(get<1>(params)),
	developpeur_(get<2>(params)),
	concepteurs_(get<3>(params))
	{};