/*
    Auteur : Max Bleriot Mba Fossi - 2417938 : Roosevelt Sonfack Ngoune - 2464064
    Date : 04/21/2026
    Créé le : 04/08/2026
*/
namespace controlleur {
    class Echiquier;
}

namespace modele {
    class GestionDeplacement {
            
        public:
            // Constructeur : on bouge la pièce et on sauvegarde où elle était
            GestionDeplacement(Echiquier& echiquier, int depart, int destination)
                : echiquier_(echiquier), depart_(depart), destination_(destination)
            {
                // On effectue le mouvement temporaire dans l'échiquier
                echiquier_.deplacerInterne(depart_, destination_);
            }

            // Destructeur : appelé AUTOMATIQUEMENT à la fin du bloc { }
            ~GestionDeplacement() {
                // On remet la pièce à sa place initiale
                echiquier_.deplacerInterne(destination_, depart_);
            }

            // On interdit la copie pour éviter les accidents de mouvements multiples
            GestionDeplacement(const GestionDeplacement&) = delete;
            GestionDeplacement& operator=(const GestionDeplacement&) = delete;
            
        private:
            Echiquier& echiquier_;
            int depart_;
            int destination_;
        };
    
};