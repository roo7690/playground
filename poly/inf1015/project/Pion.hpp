/*
	Auteur : Max Bleriot Mba Fossi - 2417938 : Roosevelt Sonfack Ngoune - 2464064
	Date : 04/21/2026
	Cr�� le : 04/08/2026
*/

#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Utils.hpp"

namespace modele {
	class Pion {
	public:
		Pion() = default;
		~Pion() { std::cout << "DESTROY Pion " << id_ << std::endl; };// = default;
		Pion(int id, bool enJeu, int equipe, std::pair<int, int> position) :
			id_(id), enJeu_(enJeu), equipe_(equipe), position_(position), premierDeplacement_(true)
		{
			image_ = (equipe_ == Constants::EquipeBlanc)
					? "images/pion_b.png"
					: "images/pion_n.png";
		}
		virtual void mouvement() {
			mouvement_.clear();
			if (premierDeplacement_) {
				if (equipe_ == Constants::EquipeNoir) {
					mouvement_.push_back({ position_.first + 1, position_.second });
					mouvement_.push_back({ position_.first + 2, position_.second });
				}
				if (equipe_ == Constants::EquipeBlanc) {
					mouvement_.push_back({ position_.first - 1, position_.second });
					mouvement_.push_back({ position_.first - 2, position_.second });
				}
				premierDeplacement_ = false;
			}
			else{
				if (equipe_ == Constants::EquipeNoir)
					mouvement_.push_back({ position_.first + 1, position_.second });
				if (equipe_ == Constants::EquipeBlanc)
					mouvement_.push_back({ position_.first - 1, position_.second });
			}			

		}
		std::vector<std::pair<int, int>> getMouvement() const {
			return mouvement_;
		}
		std::string getImage() {
			return image_;
		}
		int getId() {
			return id_;
		}		
		void setPosition(std::pair<int, int> position) {
			position_ = position;
		}
	private:
		bool premierDeplacement_;
	protected:
		int id_;
		bool enJeu_;
		int equipe_;
		std::pair<int, int> position_;
		std::vector<std::pair<int, int>> mouvement_;
		std::string image_;

	};
}  