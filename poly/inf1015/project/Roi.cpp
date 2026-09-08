/*
	Auteur : Max Bleriot Mba Fossi - 2417938 : Roosevelt Sonfack Ngoune - 2464064
	Date : 04/21/2026
	Cr�� le : 04/08/2026
*/
#include "Roi.hpp"

namespace modele {
	int Roi::nombreRois = 0;
	Roi::Roi() {				
		verifieRoi();		
		nombreRois++;
	}
	Roi::Roi(int id, bool enJeu, int equipe, std::pair<int, int> position) :
		Pion(id, enJeu, equipe, position) {
		verifieRoi();
		if(equipe_ == Constants::EquipeBlanc)
			image_ = "images/roi_b.png";
		else
			image_ = "images/roi_n.png";
		mouvement();
		nombreRois++;		
	}
	Roi::~Roi() {
		nombreRois--;
	}
	void Roi::mouvement() {
		mouvement_.clear();
		mouvement_.push_back({ position_.first, position_.second + 1 });
		mouvement_.push_back({ position_.first, position_.second - 1 });
		mouvement_.push_back({ position_.first - 1, position_.second - 1 });
		mouvement_.push_back({ position_.first - 1, position_.second });
		mouvement_.push_back({ position_.first - 1, position_.second + 1 });
		mouvement_.push_back({ position_.first + 1, position_.second - 1 });
		mouvement_.push_back({ position_.first + 1, position_.second });
		mouvement_.push_back({ position_.first + 1, position_.second + 1 });
	}
	void Roi::verifieRoi() {
    if(nombreRois >= 2)
	    throw std::runtime_error("Erreur : Impossible de cr�er plus de 2 rois.");
	}
}