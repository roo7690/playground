/*
	Auteur : Max Bleriot Mba Fossi - 2417938 : Roosevelt Sonfack Ngoune - 2464064
	Date : 04/21/2026
	Créé le : 04/08/2026
*/
#include "Pion.hpp"
#include "Utils.hpp"

#pragma once

namespace modele {
	class Roi : public Pion {
	public:
		Roi();
		Roi(int id, bool enJeu, int equipe, std::pair<int, int> position);
		~Roi();
		void verifieRoi();
		void mouvement();
	private:
		static int nombreRois;
	};
}