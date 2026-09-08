#include "Concepteur.hpp"

// Constructeur parametre
Concepteur::Concepteur(tuple<string, int, string> params) :
	nom_(get<0>(params)),
	anneeNaissance_(get<1>(params)),
	pays_(get<2>(params))
	{};