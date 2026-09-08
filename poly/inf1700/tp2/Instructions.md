# Instructions pour le TP2 - Automne 2025

## Information générale
* En cas de difficultés, il est toujours possible de modifier des fichiers [directement sur GitHub](https://docs.github.com/en/github/managing-files-in-a-repository/editing-files-in-your-repository)
* Pour toute question, consultez d'abord les forums Moodle/Discord du cours

### Préparation pour le TP2

1. **Cloner le repository**
   ```bash
   git clone https://github.com/INF1007-Gabarits/2025A-TP2.git
   ```
   Ou via GitHub Desktop : File → Clone Repository

2. **Structure des fichiers**
   ```
   TP2/
   ├── README.md           # Énoncé du TP
   ├── instructions.md     # Ce fichier
   ├── exercice1.py       # Gestion du menu
   ├── exercice2.py       # File d'attente
   ├── exercice3.py       # Inventaire
   ├── exercice4.py       # Réservations
   ├── exercice5.py       # Satisfaction client
   ├── bonus.py           # Mini-jeu (optionnel)
   └── test_tp2.py        # Tests automatiques
   ```

3. **Ouvrir le projet dans votre IDE**
   * PyCharm : File → Open → Sélectionner le dossier TP2-automne2024
   * VS Code : File → Open Folder → Sélectionner le dossier

## Pendant le TP

### Workflow recommandé

1. **Avant de commencer à coder**
   ```bash
   git pull  # Récupérer les dernières modifications
   ```

2. **Lire attentivement le README.md**
   * Comprendre chaque exercice avant de coder
   * Noter les points importants et contraintes

3. **Compléter les exercices**
   * Modifier UNIQUEMENT les sections marquées `TODO`

4. **Tester votre code**
   * Exécuter chaque exercice individuellement :
   ```bash
   python Exercice1.py
   python Exercice2.py
   # etc.
   ```
   * Exécuter les tests automatiques :
   ```bash
   python tp2_tests.py
   ```

### Conseils de débogage

1. **Utilisez les print() pour déboguer**
   ```python
   print(f"DEBUG: variable = {variable}")
   ```

2. **Testez avec les exemples fournis**
   * Chaque exercice contient des cas de test dans le `if __name__ == '__main__':`

3. **Erreurs fréquentes à éviter**
   * Index hors limites dans les listes
   * Division par zéro (vérifier les dénominateurs)
   * Oubli de conversion de types (str → int)
   * Modification d'une liste pendant son parcours

## Remise du TP

### Format de remise
1. **Créer une archive ZIP**
   * Nommer le fichier : `LXX-YY-TP2.zip`
   * XX = numéro de section de laboratoire
   * YY = numéro d'équipe

2. **Contenu de l'archive**
   * Tous les fichiers .py modifiés
   * NE PAS inclure les dossiers __pycache__ ou .git

3. **Soumettre sur Moodle**
   * Date limite : **Dimanche 19 octobre 2025 à 23h59**
   * Pénalité de retard : -10% par jour

### Critères d'évaluation
* Fonctionnalité (60%) : Le code produit les résultats attendus
* Qualité du code (20%) : Lisibilité, structure, nommage
* Respect des consignes (10%) : Format, contraintes respectées
* Tests (10%) : Tous les tests passent

## Support et ressources

### Documentation Python
* [Documentation officielle Python](https://docs.python.org/fr/3/)
* [Tutorial Python](https://docs.python.org/fr/3/tutorial/)

### Structures de données
* [Listes](https://docs.python.org/fr/3/tutorial/datastructures.html#more-on-lists)
* [Dictionnaires](https://docs.python.org/fr/3/tutorial/datastructures.html#dictionaries)
* [Tuples](https://docs.python.org/fr/3/tutorial/datastructures.html#tuples-and-sequences)

### Aide supplémentaire
* Forum Moodle du cours
* Discord du cours

---

Bon courage pour le TP2 ! 🚀
