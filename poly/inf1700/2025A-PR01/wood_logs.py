import pygame
from config import LOG_SIZES

# ======================== PARTIE 3.1 ===========================
# 
# Définir un dictionnaire pour les bûches en bois avec trois tailles différentes : petite, moyenne et longue
# 
# Étapes à suivre : 
# - Créer un dictionnaire nommé `logs_dict` avec les trois clés suivantes : 
#      - short
#      - medium
#      - long 
#
# - Utilisez "pygame.image.load()" pour charger l'image "log.png" (à partir du dossier "images/")
#   trois fois, c'est-à-dire une fois pour chaque taille.
# - Redimensionnez (avec "pygame.transform.scale") chaque image en utilisant les clés du dictionnaire LOG_SIZES. 

logs_dict = { "short": None, "medium": None, "long": None }

log = pygame.image.load('images/log.png')

for size in logs_dict :
  logs_dict[size] = pygame.transform.scale(log, LOG_SIZES[size])

# ===============================================================