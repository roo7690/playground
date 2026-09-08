# TP2: Simulateur de Restaurant "Python Bistro" 🍳

#### ⏰ Date de remise : Dimanche 19 octobre 2025 à 23h59

## Objectif
Ce TP vous permettra d'apprendre la programmation Python à travers la création d'un simulateur de gestion de restaurant. Vous allez découvrir et maîtriser :
- Les structures de contrôle (boucles, conditions)
- Les structures de données (listes, dictionnaires, tuples)
- Les algorithmes de base (tri, recherche, optimisation)
- La manipulation de données complexes

## Introduction
Félicitations ! Vous venez d'hériter du restaurant familial "Python Bistro". Pour moderniser l'établissement, vous devez créer un système de gestion informatisé qui permettra de :
- Gérer les commandes des clients
- Optimiser l'inventaire des ingrédients
- Calculer les profits
- Créer un système de réservation
- Gérer la satisfaction client

## Structure du TP
Le TP est divisé en 5 exercices indépendants (+ un bonus optionnel) qui simulent différents aspects de la gestion du restaurant. Chaque exercice contient plusieurs fonctions marquées `# TODO` : **ne modifiez que ces sections**.

---

## Exercice 1: Gestion du Menu (3 points)
Vous devez compléter les fonctions liées au menu. Le menu est représenté par un dictionnaire où les clés sont les noms des plats et les valeurs sont des tuples `(prix, temps_preparation, popularité)`.

Fonctions à compléter (`TODO`) :
- `analyser_menu(menu)`  
  - Trouver le plat le plus rentable (rapport `popularité / temps_preparation`, **gérer `temps_preparation == 0` en l'ignorant, retourner `None` si tous les plats ont temps = 0**).
  - Calculer le prix moyen du menu.
  - Calculer le temps de préparation moyen.
  - Retourner un dictionnaire de statistiques (`'plat_plus_rentable'`, `'prix_moyen'`, `'temps_moyen'`).
  - **En cas d'égalité de ratio, retourner le premier plat trouvé. Menu vide : retourner `None` pour `plat_plus_rentable`, `0` pour les moyennes.**

- `filtrer_menu_par_categorie(menu, categories)`  
  - Organiser le menu par catégories (ex. `{'entrées': [...], 'plats': [...], 'desserts': [...]}`).
  - **Gérer le cas où des plats n'ont pas de catégorie : les ignorer silencieusement.**

- `calculer_profit(menu, ventes_jour)`  
  - Calculer le profit total pour la journée : somme de `prix_plat * nombre_ventes` pour chaque plat vendu.
  - **Gérer les plats absents du menu : ignorer ces ventes (pas d'erreur).**

**Exemple :**
```python
menu = {
    'Pizza Margherita': (12.50, 15, 8),
    'Pâtes Carbonara': (14.00, 12, 9),
    'Salade César': (9.50, 5, 6),
    'Tiramisu': (6.00, 3, 10)
}
```

**💡 Astuce** : Les dictionnaires peuvent avoir des champs manquants. Utilisez `dict.get('champ', valeur_defaut)` pour éviter les erreurs.

**Exemple :**
```python
temps = commande.get('temps_attente', 0)  # 0 si le champ n'existe pas
vip = commande.get('client_vip', False)   # False par défaut
```
---

## Exercice 2: File d'attente des commandes (4 points)
Les commandes arrivent en cuisine et doivent être priorisées. Implémentez les fonctions listées ci-dessous.

Fonctions à compléter (`TODO`) :
- `calculer_priorite(commande)`  
  - Implémenter la formule : `Score = (temps_attente × 2) + (nombre_items × 1) + (client_vip × 10)` (le booléen `client_vip` vaut 1 si True, 0 sinon).
  - **Si une commande n'a pas tous les champs requis, utiliser 0 comme valeur par défaut.**

- `trier_commandes(liste_commandes)`  
  - Trier les commandes par priorité décroissante (commandes avec score le plus élevé en premier).
  - Implémenter un algorithme de tri (ex. tri à bulles, insertion, etc.) sans utiliser `sorted()`.
  - Veiller à ne pas modifier la liste originale si cela doit être explicitement évité (faire une copie si nécessaire).
  - **En cas d'égalité de priorité, conserver l'ordre original des commandes.**

- `estimer_temps_total(liste_commandes_triee)`  
  - Calculer le temps total et le temps moyen pour traiter les commandes.
  - Hypothèse : **chaque item prend en moyenne 3 minutes**.

- `identifier_commandes_urgentes(liste_commandes, seuil_attente=30)`  
  - Retourner la liste des numéros de commandes dont `temps_attente > seuil_attente`.

---

## Exercice 3: Optimisation de l'inventaire (4 points)
Gérer l'inventaire et préparer des recettes sans ruptures.

Fonctions à compléter (`TODO`) :
- `verifier_disponibilite(inventaire, recette)`  
  - Vérifier, ingrédient par ingrédient, si l'inventaire suffit pour la recette.
  - Retourner `(peut_preparer: bool, ingredients_manquants: list)`.
  - **Si un ingrédient requis par une recette n'existe pas dans l'inventaire, le considérer comme ayant une quantité de 0.**

- `mettre_a_jour_inventaire(inventaire, recette, quantite=1)`  
  - Soustraire les quantités utilisées selon `recette`, multipliées par `quantite`.
  - Retourner le nouvel inventaire (copie, ne pas modifier l'original si nécessaire).

- `generer_alertes_stock(inventaire, seuil=10)`  
  - Identifier les ingrédients avec stock < `seuil`.
  - Suggérer une quantité à commander (ex. commander jusqu'à 50 unités : `a_commander = max(0, 50 - stock_actuel)`).
  - Retourner un dict `{ingredient: (quantité_actuelle, quantité_à_commander)}`.

- `calculer_commandes_possibles(inventaire, menu_recettes)`  
  - Pour chaque plat, calculer combien de portions peuvent être préparées avec l'inventaire actuel.
  - Le nombre possible est le minimum des `inventaire[ingredient] // besoin_par_portion`.

- `optimiser_achats(inventaire, menu_recettes, previsions_ventes, budget)`  
  - Calculer les besoins totaux selon les prévisions (`previsions_ventes`).
  - Soustraire l'inventaire actuel pour obtenir les besoins d'achat.
  - Optimiser selon le budget (respecter le budget en coût unitaire donné).
  - Retourner `{ingredient: quantite_a_acheter}`.

---

## Exercice 4: Système de réservation (4 points)
Créer et gérer la salle, réserver des tables et produire des rapports.

Fonctions à compléter (`TODO`) :

### Partie 1 : Initialisation (2 points)
- `initialiser_salle(nb_rangees, nb_colonnes, positions_tables)`  
  - Créer une grille remplie de `'X'` (espace non disponible).
  - Placer les tables aux positions indiquées en utilisant `'L2'` ou `'L4'` pour tables libres.

- `marquer_reservation(salle, position, taille_groupe)`  
  - Marquer la table comme réservée : `'R2'` ou `'R4'` selon la table.
  - Faire une copie sûre de la grille si nécessaire.
  - **Ne modifier que les tables libres (ignorer si la position ne contient pas une table libre).**

### Partie 2 : Recherche de table (3 points)
- `calculer_score_table(position, taille_table, taille_groupe, nb_colonnes)`  
  - Retourner `-1` si la table ne convient pas (`taille_table < taille_groupe`).
  - Base : 100 points.
  - Pénalité : `-10` points par place vide (gaspillage).
  - Bonus fenêtre : `+20` si `colonne == 0` ou `colonne == nb_colonnes - 1`.
  - Bonus position : `+5` si `rangée < 3` (près de l'entrée).

- `trouver_meilleure_table(salle, taille_groupe)`  
  - Parcourir les tables libres (`'L2'` / `'L4'`) et retourner la meilleure `(position, taille_table)`.
  - **Ne considérer que les tables libres (commençant par 'L'). Si plusieurs tables ont le même score, retourner la première trouvée.**

- `generer_rapport_occupation(salle)`  
  - Compter tables libres, réservées et occupées (`'O2'` / `'O4'`) par capacité (2 et 4).
  - Calculer le taux d'occupation (`(réservées + occupées) / total_tables`).

---

## Exercice 5: Analyse de la satisfaction client (5 points)
Analyser les commentaires clients et produire un rapport.

Fonctions à compléter (`TODO`) :
- `analyser_commentaire(commentaire, mots_cles)`  
  - Rechercher chaque mot-clé et additionner les scores.
  - Produire la liste `mots_trouves`.
  - Borner le score final entre `0` et `10`.
  - **La recherche de mots-clés doit être insensible à la casse. Un mot-clé correspond s'il est présent dans le commentaire (recherche par substring).**

- `categoriser_commentaires(liste_commentaires, mots_cles)`  
  - Analyser chaque commentaire et le classer :
    - `'positifs'` : score >= 7
    - `'neutres'` : 4 ≤ score ≤ 6
    - `'negatifs'` : score < 4
  - Stocker tuples `(texte_commentaire, score)` dans chaque catégorie.

- `identifier_problemes(commentaires_negatifs, mots_cles_negatifs)`  
  - Compter la fréquence (nombre d'apparitions) de mots-clés négatifs dans les commentaires négatifs.
  - Retourner un dict trié par fréquence décroissante.

- `generer_rapport_satisfaction(categories, frequence_problemes)`  
  - Calculer la satisfaction moyenne.
  - Calculer la distribution en pourcentages (positifs / neutres / négatifs).
  - S'il y a plus de commentaires positifs que négatifs, le champ 'points forts' sera simplement la liste ['Service apprécié', 'Qualité reconnue']. Sinon, retournez une liste vide [].
  - Identifier les 3 principaux points d'amélioration (3 mots-clés négatifs les plus fréquents).

- `calculer_tendance(historique_scores)`  
  - Déterminer `'amélioration'`, `'stable'` ou `'dégradation'` selon l'évolution des scores moyens sur les périodes.

---

## Bonus: Mini-jeu de service (2 points)
Créer un mini-jeu console (optionnel) : fonctions `TODO` à compléter :
- `initialiser_restaurant()` : créer la grille 5x5, placer la cuisine `K` et les tables (`T`).
- `deplacer_serveur(grille, serveur_pos, direction)` : déplacer le serveur avec bornes.
- `prendre_commande(...)` et `livrer_commande(...)` : logique de prise et livraison (points).
- `generer_nouveaux_clients(...)` : faire apparaître des clients aléatoirement.
- Boucle principale `jouer()` : orchestrer le jeu (affichage, entrée, génération clients, score).

---

## Consignes importantes
- **Modifiez uniquement** les sections marquées `# TODO`.
- N'importe quel import supplémentaire est interdit (ne pas ajouter de librairies externes).
- Testez votre code avec les exemples fournis dans chaque fichier (`if __name__ == '__main__':`).
- Assurez-vous que vos fonctions ne lèvent pas d'exceptions non gérées pour des entrées similaires aux exemples fournis.
- Rédigez des messages d'erreur clairs si vous gérez des cas invalides.

---
## 🚨 Erreurs courantes à éviter

### KeyError lors de l'accès aux dictionnaires
**Problème** : `KeyError: 'temps_attente'` quand une clé n'existe pas

**Solution** : 
```python
# Au lieu de :
score = commande['temps_attente'] * 2  

# Utilisez :
score = commande.get('temps_attente', 0) * 2  
```

### Division par zéro
**Problème** : `ZeroDivisionError` dans les calculs de ratios

**Solution** :
```python
# Vérifiez avant de diviser
if temps > 0:
    ratio = popularite / temps
```

### IndexError avec les listes
**Problème** : Accès à un index inexistant

**Solution** :
```python
# Vérifiez la taille de la liste
if 0 <= index < len(liste):
    valeur = liste[index]
```
---

# Barème de correction

Le barème de correction est le suivant :  

| Partie | Tâche | Points |
|--------|-------|--------|
| **Exercice 1 : Gestion du menu** | | **/3** |
| 1.1 | Calcul correct du plat le plus rentable (ratio popularité/temps, gérer temps = 0) (`analyser_menu`) | 1.0 |
| 1.2 | Calcul du prix moyen du menu (`analyser_menu`) | 0.5 |
| 1.3 | Calcul du temps de préparation moyen (`analyser_menu`) | 0.5 |
| 1.4 | Filtrage du menu par catégorie (`filtrer_menu_par_categorie`) — structure correcte | 0.5 |
| 1.5 | Calcul du profit journalier correct (`calculer_profit`) | 0.5 |
| **Exercice 2 : File d'attente des commandes** | | **/4** |
| 2.1 | Calcul correct du score de priorité (`calculer_priorite`) | 1.0 |
| 2.2 | Tri par priorité décroissante (algorithme fonctionnel, stabilité appréciée) (`trier_commandes`) | 1.0 |
| 2.3 | Estimation du temps total et temps moyen (3 min / item) (`estimer_temps_total`) | 0.75 |
| 2.4 | Identification correcte des commandes urgentes (seuil) (`identifier_commandes_urgentes`) | 0.75 |
| 2.5 | Implémentation robuste du tri (gestion des copies, pas d'effets de bord) | 0.5 |
| **Exercice 3 : Optimisation de l'inventaire** | | **/4** |
| 3.1 | Vérification correcte de la disponibilité d'une recette (`verifier_disponibilite`) | 1.0 |
| 3.2 | Mise à jour de l'inventaire après préparation (multiplie par `quantite`) (`mettre_a_jour_inventaire`) | 1.0 |
| 3.3 | Génération d'alertes de stock (< seuil) et suggestion de quantité à commander (`generer_alertes_stock`) | 0.75 |
| 3.4 | Calcul du nombre de portions possibles par plat (ingrédient limitant) (`calculer_commandes_possibles`) | 0.75 |
| 3.5 | Optimisation des achats selon prévisions et budget (priorisation raisonnable) (`optimiser_achats`) | 0.5 |
| **Exercice 4 : Système de réservation** | | **/4** |
| 4.1 | Initialisation correcte de la salle (grille `X` + placement des tables) (`initialiser_salle`) | 1.0 |
| 4.2 | Marquage des réservations (R2/R4) sans altérer les autres cases (`marquer_reservation`) | 0.5 |
| 4.3 | Calcul du score de table conforme aux règles (gaspillage, fenêtre, entrée) (`calculer_score_table`) | 0.75 |
| 4.4 | Recherche de la meilleure table libre (parcours + comparaison de score) (`trouver_meilleure_table`) | 0.75 |
| 4.5 | Rapport d'occupation correct (comptages et taux d'occupation) (`generer_rapport_occupation`) | 1.0 |
| **Exercice 5 : Analyse de la satisfaction client** | | **/5** |
| 5.1 | Analyse d'un commentaire : détection mots-clés, somme des scores, borne 0—10 (`analyser_commentaire`) | 1.0 |
| 5.2 | Catégorisation correcte des commentaires (positifs ≥7, neutres 4—6, négatifs <4) (`categoriser_commentaires`) | 1.0 |
| 5.3 | Identification des problèmes récurrents dans les commentaires négatifs (`identifier_problemes`) | 1.0 |
| 5.4 | Génération de rapport : satisfaction moyenne + distribution + points d'amélioration (`generer_rapport_satisfaction`) | 1.0 |
| 5.5 | Détection correcte de la tendance à partir d'un historique (`calculer_tendance`) | 1.0 |
| **BONUS (optionnel)** | | **/2** |
| B.1 | Mini-jeu : initialisation correcte de la grille et position cuisine (`initialiser_restaurant`) | 0.5 |
| B.2 | Déplacement serveur valide et borné (`deplacer_serveur`) | 0.5 |
| B.3 | Prendre/livrer commandes fonctionnel (points associés) (`prendre_commande`, `livrer_commande`) | 1.0 |
| **Total** |  | **/20 (+ /2 bonus)** |

Bonne chance et bon appétit ! 🍽️
