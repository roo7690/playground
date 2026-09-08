/*
    Auteur : Max Bleriot Mba Fossi - 2417938 : Roosevelt Sonfack Ngoune - 2464064
    Date : 04/21/2026
    Créé le : 04/08/2026
*/

#include <qobject.h>
#include <stdlib.h>
#include <vector>
#include "Roi.hpp"
#include <algorithm>
#include "Utils.hpp"

#pragma once

namespace controlleur{
    class Echiquier : public QObject {
        Q_OBJECT
    public:
        explicit Echiquier(QObject* parent = nullptr) : QObject(parent) {
            // Initialisation de ton tableau 8x8
            setupBoard();
        }

        // Fonction que le QML pourra appeler
        Q_INVOKABLE QString getPionImage(int index) {
            int row = index / 8;
            int col = index % 8;
            if (echiquier_[row][col] != nullptr) {
                return QString::fromStdString(echiquier_[row][col]->getImage());
            }
            return ""; // Case vide
        }

        Q_INVOKABLE int getPionId(int index) {
            int row = index / 8;
            int col = index % 8;
            if (echiquier_[row][col] != nullptr) {
                return echiquier_[row][col]->getId();
            }
            return -1; // Case vide
        }

        Q_INVOKABLE QList<int> getPossibilitePion(int index) {
            int row = index / 8;
            int col = index % 8;
            QList<int> moves;
            if (echiquier_[row][col] != nullptr) {
                auto possibilites = CalculPossibilite(echiquier_[row][col]);
                for (auto move : possibilites) {
                    moves.push_back(move.first * 8 + move.second);
                }
            }
            return moves;
        }

        modele::Pion*** getEchiquier() const {
            return (modele::Pion***)echiquier_;
        }
        
        Q_INVOKABLE void deplacerPion(int depart, int destination) {
            int r1 = depart / 8;
            int c1 = depart % 8;
            int r2 = destination / 8;
            int c2 = destination % 8;
            std::cout << "Je bouge " << r2 << " : " << c2 << std::endl;
            if (echiquier_[r1][c1] != nullptr && echiquier_[r2][c2] == nullptr) {
                auto possibilites = CalculPossibilite(echiquier_[r1][c1]);
                std::cout << "Je bouge 2" << std::endl;
                if (std::find(possibilites.begin(), possibilites.end(), std::make_pair(r2, c2)) != possibilites.end()) {
                    std::cout << "Je bouge 3" << std::endl;
                    echiquier_[r1][c1]->setPosition(std::make_pair(r2, c2));
                    echiquier_[r2][c2] = echiquier_[r1][c1];

                    echiquier_[r1][c1] = nullptr;
                }
                emit caseUpdate();
            }
        }

        std::vector<std::pair<int, int>> CalculPossibilite(modele::Pion* p) {
            std::vector<std::pair<int, int>> possibilites;
            if (p) {
                auto moves = p->getMouvement();
                for (auto move : moves) {
                    if (move.first >= 0 && move.first < 8 && move.second >= 0 && move.second < 8 && echiquier_[move.first][move.second] == nullptr)
                        possibilites.push_back(move);
                }
            }
            return possibilites;
        }

    private:
        modele::Pion* echiquier_[8][8];
        void setupBoard() {
            // Logique pour placer tes objets Pion/Roi dans la grille
            modele::Pion* p1 = new modele::Pion(1, true, Constants::EquipeBlanc, { 1, 0 });
            modele::Pion* p2 = new modele::Pion(2, true, Constants::EquipeNoir, { 7, 2 });
            try {
                modele::Roi* r1 = new modele::Roi(3, true, Constants::EquipeBlanc, { 1, 1 });
                echiquier_[1][1] = r1;
                modele::Roi* r2 = new modele::Roi(4, true, Constants::EquipeNoir, { 4, 4 });
                echiquier_[4][4] = r2;
                modele::Roi* r3 = new modele::Roi(5, true, Constants::EquipeBlanc, { 6, 7 });
            }
            catch (const std::runtime_error& e) {
                // C'est ici que l'on "rattrape" l'erreur lancée par le modèle
                std::cout << e.what();
            }
            echiquier_[0][0] = p1;
            echiquier_[7][2] = p2;                        
        }
        std::vector<std::vector<int>> board;
    signals:
        void caseUpdate();
    };
}
