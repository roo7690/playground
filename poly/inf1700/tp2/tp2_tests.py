"""
Tests automatiques pour le TP2 - Python Bistro
Automne 2025

Utilisation:
    python test_tp2.py

Note: Les imports doivent être modifiés selon les noms de vos fichiers
"""

import unittest
import sys
import os

# Importer les modules à tester
try:
    import Exercice1 as ex1
    import Exercice2 as ex2
    import Exercice3 as ex3
    import Exercice4 as ex4
    import Exercice5 as ex5
except ImportError as e:
    print(f"Erreur d'importation: {e}")
    print("Assurez-vous que tous les fichiers exerciceX.py sont présents")
    sys.exit(1)


class TestExercice1(unittest.TestCase):
    """Tests pour l'exercice 1 : Gestion du menu"""
    
    def setUp(self):
        self.menu_test = {
            'Pizza Margherita': (12.50, 15, 8),
            'Pâtes Carbonara': (14.00, 12, 9),
            'Salade César': (9.50, 5, 6),
            'Tiramisu': (6.00, 3, 10),
        }
    
    def test_analyser_menu_plat_rentable(self):
        """Test du calcul du plat le plus rentable"""
        stats = ex1.analyser_menu(self.menu_test)
        # Tiramisu a le meilleur ratio: 10/3 = 3.33
        self.assertEqual(stats['plat_plus_rentable'], 'Tiramisu')
    
    def test_analyser_menu_prix_moyen(self):
        """Test du calcul du prix moyen"""
        stats = ex1.analyser_menu(self.menu_test)
        prix_moyen_attendu = (12.50 + 14.00 + 9.50 + 6.00) / 4
        self.assertAlmostEqual(stats['prix_moyen'], prix_moyen_attendu, places=2)
    
    def test_analyser_menu_temps_moyen(self):
        """Test du calcul du temps moyen"""
        stats = ex1.analyser_menu(self.menu_test)
        temps_moyen_attendu = (15 + 12 + 5 + 3) / 4
        self.assertAlmostEqual(stats['temps_moyen'], temps_moyen_attendu, places=1)
    
    def test_analyser_menu_vide(self):
        """Test avec un menu vide"""
        stats = ex1.analyser_menu({})
        self.assertIsNone(stats.get('plat_plus_rentable'))
        self.assertEqual(stats.get('prix_moyen', 0), 0)
    
    def test_filtrer_menu_par_categorie(self):
        """Test du filtrage par catégorie"""
        categories = {
            'Pizza Margherita': 'plats',
            'Pâtes Carbonara': 'plats',
            'Salade César': 'entrées',
            'Tiramisu': 'desserts'
        }
        resultat = ex1.filtrer_menu_par_categorie(self.menu_test, categories)
        
        self.assertIn('plats', resultat)
        self.assertIn('entrées', resultat)
        self.assertIn('desserts', resultat)
        self.assertEqual(len(resultat['plats']), 2)
        self.assertEqual(len(resultat['entrées']), 1)
        self.assertEqual(len(resultat['desserts']), 1)
    
    def test_calculer_profit(self):
        """Test du calcul de profit"""
        ventes = {
            'Pizza Margherita': 10,
            'Tiramisu': 5
        }
        profit = ex1.calculer_profit(self.menu_test, ventes)
        profit_attendu = (12.50 * 10) + (6.00 * 5)
        self.assertEqual(profit, profit_attendu)


class TestExercice2(unittest.TestCase):
    """Tests pour l'exercice 2 : File d'attente"""
    
    def setUp(self):
        self.commandes = [
            {'numero': 1, 'temps_attente': 10, 'nombre_items': 3, 'client_vip': False},
            {'numero': 2, 'temps_attente': 25, 'nombre_items': 2, 'client_vip': True},
            {'numero': 3, 'temps_attente': 5, 'nombre_items': 5, 'client_vip': False},
        ]
    
    def test_calculer_priorite_normal(self):
        """Test du calcul de priorité pour client normal"""
        commande = {'temps_attente': 10, 'nombre_items': 3, 'client_vip': False}
        priorite = ex2.calculer_priorite(commande)
        # (10 * 2) + (3 * 1) + 0 = 23
        self.assertEqual(priorite, 23)
    
    def test_calculer_priorite_vip(self):
        """Test du calcul de priorité pour client VIP"""
        commande = {'temps_attente': 10, 'nombre_items': 3, 'client_vip': True}
        priorite = ex2.calculer_priorite(commande)
        # (10 * 2) + (3 * 1) + 10 = 33
        self.assertEqual(priorite, 33)
    
    def test_trier_commandes(self):
        """Test du tri des commandes"""
        commandes_triees = ex2.trier_commandes(self.commandes.copy())
        # Commande 2 (VIP avec attente) devrait être première
        self.assertEqual(commandes_triees[0]['numero'], 2)
    
    def test_estimer_temps_total(self):
        """Test de l'estimation du temps"""
        temps_stats = ex2.estimer_temps_total(self.commandes)
        # (3 + 2 + 5) * 3 minutes = 30 minutes
        self.assertEqual(temps_stats['temps_total'], 30)
        self.assertEqual(temps_stats['temps_moyen'], 10)
    
    def test_identifier_commandes_urgentes(self):
        """Test de l'identification des commandes urgentes"""
        urgentes = ex2.identifier_commandes_urgentes(self.commandes, seuil_attente=20)
        self.assertIn(2, urgentes)  # Commande 2 a 25 min d'attente
        self.assertNotIn(1, urgentes)
        self.assertNotIn(3, urgentes)


class TestExercice3(unittest.TestCase):
    """Tests pour l'exercice 3 : Inventaire"""
    
    def setUp(self):
        self.inventaire = {
            'tomates': 50,
            'fromage': 30,
            'pâtes': 100,
            'sauce': 25
        }
        self.recettes = {
            'Pizza': {'tomates': 5, 'fromage': 3},
            'Pâtes': {'pâtes': 10, 'sauce': 2}
        }
    
    def test_verifier_disponibilite_ok(self):
        """Test vérification avec ingrédients disponibles"""
        dispo, manquants = ex3.verifier_disponibilite(
            self.inventaire, self.recettes['Pizza']
        )
        self.assertTrue(dispo)
        self.assertEqual(len(manquants), 0)
    
    def test_verifier_disponibilite_manque(self):
        """Test vérification avec ingrédients manquants"""
        recette_impossible = {'tomates': 100, 'fromage': 50}
        dispo, manquants = ex3.verifier_disponibilite(
            self.inventaire, recette_impossible
        )
        self.assertFalse(dispo)
        self.assertIn('tomates', manquants)
        self.assertIn('fromage', manquants)
    
    def test_mettre_a_jour_inventaire(self):
        """Test mise à jour de l'inventaire"""
        nouvel_inv = ex3.mettre_a_jour_inventaire(
            self.inventaire, self.recettes['Pizza'], 2
        )
        # 50 - (5*2) = 40 tomates
        self.assertEqual(nouvel_inv['tomates'], 40)
        # 30 - (3*2) = 24 fromage
        self.assertEqual(nouvel_inv['fromage'], 24)
    
    def test_generer_alertes_stock(self):
        """Test génération d'alertes"""
        inv_faible = {'tomates': 5, 'fromage': 30}
        alertes = ex3.generer_alertes_stock(inv_faible, seuil=10)
        
        self.assertIn('tomates', alertes)
        self.assertNotIn('fromage', alertes)
        # Vérifier la quantité à commander
        self.assertEqual(alertes['tomates'][0], 5)  # Stock actuel
    
    def test_calculer_commandes_possibles(self):
        """Test calcul des portions possibles"""
        possibles = ex3.calculer_commandes_possibles(
            self.inventaire, self.recettes
        )
        # Pizza: min(50/5, 30/3) = min(10, 10) = 10
        self.assertEqual(possibles['Pizza'], 10)
        # Pâtes: min(100/10, 25/2) = min(10, 12) = 10
        self.assertEqual(possibles['Pâtes'], 10)

    def test_optimiser_achats(self):
        """Test optimisation des achats avec budget limité"""
        previsions = {'Pizza': 10, 'Pâtes': 5}
        budget = 50.0
        
        achats = ex3.optimiser_achats(
            self.inventaire, self.recettes, previsions, budget
         )   
        
         # Vérifier que le budget n'est pas dépassé
        cout_total = sum(
             achats.get(ing, 0) * cout 
             for ing, cout in {'tomates': 0.5, 'fromage': 2.0, 'pâtes': 1.0, 'sauce': 1.5}.items()
        )
        self.assertLessEqual(cout_total, budget)
        
        # Vérifier que les quantités sont positives
        for quantite in achats.values():
             self.assertGreaterEqual(quantite, 0)


class TestExercice4(unittest.TestCase):
    """Tests pour l'exercice 4 : Système de réservation"""
    
    def test_initialiser_salle(self):
        """Test initialisation de la salle"""
        positions = [(0, 0, 2), (1, 1, 4), (2, 2, 2)]
        salle = ex4.initialiser_salle(3, 3, positions)
        
        self.assertEqual(salle[0][0], 'L2')
        self.assertEqual(salle[1][1], 'L4')
        self.assertEqual(salle[2][2], 'L2')
        self.assertEqual(salle[0][1], 'X')  # Espace non disponible
    
    def test_marquer_reservation(self):
        """Test marquage de réservation"""
        salle = [['L2', 'X'], ['X', 'L4']]
        nouvelle_salle = ex4.marquer_reservation(salle, (0, 0), 2)
        
        self.assertEqual(nouvelle_salle[0][0], 'R2')
        self.assertEqual(nouvelle_salle[1][1], 'L4')  # Inchangé
    
    def test_calculer_score_table_parfait(self):
        """Test calcul score table parfaite"""
        # Table de 2 pour groupe de 2, près fenêtre
        score = ex4.calculer_score_table((0, 0), 2, 2, 5)
        # 100 + 20 (fenêtre) + 5 (près entrée) = 125
        self.assertEqual(score, 125)
    
    def test_calculer_score_table_trop_petite(self):
        """Test table trop petite"""
        score = ex4.calculer_score_table((0, 0), 2, 3, 5)
        self.assertEqual(score, -1)
    
    def test_trouver_meilleure_table(self):
        """Test recherche meilleure table"""
        salle = [
            ['L2', 'X', 'L4'],
            ['X', 'R2', 'X'],
            ['L4', 'X', 'L2']
        ]
        meilleure = ex4.trouver_meilleure_table(salle, 3)
        
        self.assertIsNotNone(meilleure)
        position, taille = meilleure
        self.assertIn(taille, [4])  # Seules tables de 4 conviennent
    
    def test_generer_rapport_occupation(self):
        """Test génération rapport"""
        salle = [
            ['L2', 'R2', 'O4'],
            ['X', 'L4', 'X']
        ]
        rapport = ex4.generer_rapport_occupation(salle)
        
        self.assertEqual(rapport['tables_libres_2'], 1)
        self.assertEqual(rapport['tables_libres_4'], 1)
        self.assertEqual(rapport['tables_reservees_2'], 1)
        self.assertEqual(rapport['tables_occupees_4'], 1)
        # Taux occupation: 2/4 = 50%
        self.assertAlmostEqual(rapport['taux_occupation'], 0.5, places=2)


class TestExercice5(unittest.TestCase):
    """Tests pour l'exercice 5 : Satisfaction client"""
    
    def setUp(self):
        self.mots_cles = {
            'excellent': 3, 'délicieux': 2, 'rapide': 1,
            'froid': -2, 'lent': -3, 'décevant': -2
        }
    
    def test_analyser_commentaire_positif(self):
        """Test analyse commentaire positif"""
        score, mots = ex5.analyser_commentaire(
            "Service excellent et plats délicieux!",
            self.mots_cles
        )
        # 5 + 3 + 2 = 10
        self.assertEqual(score, 10)
        self.assertIn('excellent', mots)
        self.assertIn('délicieux', mots)
    
    def test_analyser_commentaire_negatif(self):
        """Test analyse commentaire négatif"""
        score, mots = ex5.analyser_commentaire(
            "Service lent et nourriture froide",
            self.mots_cles
        )
        # 5 - 3 - 2 = 0
        self.assertEqual(score, 0)
        self.assertIn('lent', mots)
        self.assertIn('froid', mots)
    
    def test_analyser_commentaire_limites(self):
        """Test limites du score (0-10)"""
        score_max, _ = ex5.analyser_commentaire(
            "Excellent excellent excellent délicieux rapide",
            self.mots_cles
        )
        self.assertEqual(score_max, 10)  # Limité à 10
        
        score_min, _ = ex5.analyser_commentaire(
            "Lent froid décevant lent froid décevant",
            self.mots_cles
        )
        self.assertEqual(score_min, 0)  # Limité à 0
    
    def test_categoriser_commentaires(self):
        """Test catégorisation des commentaires"""
        commentaires = [
            "Excellent service!",  # Positif
            "Correct, sans plus",  # Neutre
            "Très décevant"  # Négatif
        ]
        categories = ex5.categoriser_commentaires(commentaires, self.mots_cles)
        
        self.assertEqual(len(categories['positifs']), 1)
        self.assertEqual(len(categories['neutres']), 1)
        self.assertEqual(len(categories['negatifs']), 1)
    
    def test_identifier_problemes(self):
        """Test identification problèmes"""
        commentaires_negatifs = [
            "Service lent",
            "Trop lent et froid",
            "Plat froid"
        ]
        mots_negatifs = {k: v for k, v in self.mots_cles.items() if v < 0}
        
        problemes = ex5.identifier_problemes(commentaires_negatifs, mots_negatifs)
        
        # 'lent' apparaît 2 fois, 'froid' 2 fois
        self.assertIn('lent', problemes)
        self.assertIn('froid', problemes)
        self.assertEqual(problemes['lent'], 2)
        self.assertEqual(problemes['froid'], 2)
        
    def test_generer_rapport_satisfaction(self):
        """Test génération rapport complet"""
        categories = {
            'positifs': [("Super!", 8), ("Excellent!", 9)],
            'neutres': [("Correct", 5)],
            'negatifs': [("Mauvais", 2)]
        }
        problemes = {'lent': 3, 'froid': 2}
        
        rapport = ex5.generer_rapport_satisfaction(categories, problemes)
        
        # Vérifier la structure du rapport
        self.assertIn('satisfaction_moyenne', rapport)
        self.assertIn('distribution', rapport)
        self.assertIn('points_forts', rapport)
        self.assertIn('points_amelioration', rapport)
        
        # Vérifier la satisfaction moyenne: (8+9+5+2)/4 = 6.0
        self.assertAlmostEqual(rapport['satisfaction_moyenne'], 6.0, places=1)
        
        # Vérifier la distribution
        self.assertIn('positifs', rapport['distribution'])
        self.assertIn('neutres', rapport['distribution'])
        self.assertIn('negatifs', rapport['distribution'])
        
        # Plus de positifs que négatifs -> doit avoir des points forts
        self.assertEqual(len(rapport['points_forts']), 2)
        self.assertEqual(rapport['points_forts'], ['Service apprécié', 'Qualité reconnue'])
        
        # Top 3 problèmes (ou moins si moins disponibles)
        self.assertLessEqual(len(rapport['points_amelioration']), 3)
        self.assertEqual(rapport['points_amelioration'], ['lent', 'froid'])
    
    def test_generer_rapport_majorite_negative(self):
        """Test rapport avec majorité négative (pas de points forts)"""
        categories = {
            'positifs': [("Ok", 7)],
            'neutres': [],
            'negatifs': [("Mauvais", 2), ("Terrible", 1), ("Nul", 3)]
        }
        problemes = {'lent': 5}
        
        rapport = ex5.generer_rapport_satisfaction(categories, problemes)
        
        # Plus de négatifs que positifs -> pas de points forts
        self.assertEqual(len(rapport['points_forts']), 0)
    
    def test_calculer_tendance(self):
        """Test calcul de tendance"""
        historique_amelioration = [
            ['Jan', 6.0],
            ['Fev', 6.5],
            ['Mar', 7.0],
            ['Avr', 7.5]
        ]
        self.assertEqual(
            ex5.calculer_tendance(historique_amelioration),
            'amélioration'
        )
        
        historique_degradation = [
            ['Jan', 7.5],
            ['Fev', 7.0],
            ['Mar', 6.5]
        ]
        self.assertEqual(
            ex5.calculer_tendance(historique_degradation),
            'dégradation'
        )
        
        historique_stable = [
            ['Jan', 6.5],
            ['Fev', 7.0],
            ['Mar', 6.8]
        ]
        self.assertEqual(
            ex5.calculer_tendance(historique_stable),
            'stable'
        )


def suite_tests():
    """Créer et retourner la suite de tests"""
    suite = unittest.TestSuite()
    
    # Ajouter tous les tests
    suite.addTest(unittest.makeSuite(TestExercice1))
    suite.addTest(unittest.makeSuite(TestExercice2))
    suite.addTest(unittest.makeSuite(TestExercice3))
    suite.addTest(unittest.makeSuite(TestExercice4))
    suite.addTest(unittest.makeSuite(TestExercice5))
    
    return suite


if __name__ == '__main__':
    # Configuration du runner de tests
    runner = unittest.TextTestRunner(verbosity=2)
    
    # Exécuter les tests
    print("="*60)
    print("TESTS AUTOMATIQUES - TP2 PYTHON BISTRO")
    print("="*60)
    
    resultat = runner.run(suite_tests())
    
    # Afficher le résumé
    print("\n" + "="*60)
    print("RÉSUMÉ DES TESTS")
    print("="*60)
    
    nb_tests = resultat.testsRun
    nb_echecs = len(resultat.failures)
    nb_erreurs = len(resultat.errors)
    nb_reussis = nb_tests - nb_echecs - nb_erreurs
    
    print(f"Tests exécutés : {nb_tests}")
    print(f"✓ Réussis : {nb_reussis}")
    print(f"✗ Échecs : {nb_echecs}")
    print(f"⚠ Erreurs : {nb_erreurs}")
    
    # Retourner le code de sortie approprié
    sys.exit(0 if resultat.wasSuccessful() else 1)
