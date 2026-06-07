#ifndef CONSTANTES_H
#define CONSTANTES_H

// TAILLES ET LIMITES
#define MAX_NOM_LOTO            50     /* Longueur max du nom d'un loto                    */
#define MAX_VALEURS             100    /* Nombre maximum de valeurs stockables             */
#define MAX_FICHIERS            100    /* Nombre maximum de fichiers .txt detectables      */
#define TAILLE_MAX_FICHIER      256    /* Taille max des chaines de nom de fichier         */
#define TAILLE_BUF_TEXTE        40     /* Taille max du buffer de lecture de texte         */
#define MAX_SCAN                100    /* Taille max du tableau de comparaison             */
#define NUMERO_A_JOUER          6      /* Nombre de numeros a afficher dans le top/bottom  */

#define BLOC_SAUVEGARDE 3 // Valeurs par ligne dans le fichier

// BIENVENUE / INFO
#define MSG_BIENVENUE        "=== BIENVENUE DANS L'ANALYSEUR DE LOTO ===\n"
#define MSG_CONFIG_TITLE     "\n--- CONFIGURATION DU LOTO CHARGE ---\n"
#define MSG_CONFIG_INFO      "Nom : %s | Saisies enregistrees : %d\n"
#define MSG_FICHIER_CREE     "\nFichier de configuration créé avec succès.\n"
#define MSG_SUCCESS_FICHIER  "Succes\n"
#define MSG_VALUES_AFFICHEES "Voici les valeurs lues : \n"
#define MSG_VALEUR_LUE       "%s, "
#define MSG_LOTO_EXISTANT    "Loto(s) déjà existant(s) ! Souhaitez-vous en créer un nouveau ? (o/n) "

// MENU PRINCIPAL
#define MSG_MENU_TITRE       "\n--- MENU PRINCIPAL ---\n"
#define MSG_MENU_1           "1. Inserer une nouvelle valeur\n"
#define MSG_MENU_2           "2. Modifier la derniere valeur\n"
#define MSG_MENU_3           "3. Supprimer la derniere valeur\n"
#define MSG_MENU_4           "4. Afficher la valeur la plus gagnante\n"
#define MSG_MENU_5           "5. Afficher la valeur la moins gagnante\n"
#define MSG_MENU_6           "6. Afficher les 6 meilleurs numeros\n"
#define MSG_MENU_7           "7. Afficher les 6 moins bons numeros\n"
#define MSG_MENU_8           "8. Afficher le tri des frequences\n"
#define MSG_MENU_9           "9. Afficher le nombre de tirages\n"
#define MSG_MENU_10          "10. Quitter et sauvegarder\n"
#define MSG_MENU_CHOIX       "Votre choix : "
#define MSG_MENU_VALEUR      "Valeur a inserer : "
#define MSG_MENU_MODIF       "Nouvelle valeur pour remplacer la derniere : "
#define MSG_MENU_TIRAGES     "Nombre de tirages enregistres : %d\n"

// CREATION NOUVEAU LOTO
#define MSG_CREAT_TITRE      "\n--- CREATION D'UN NOUVEAU LOTO ---\n"
#define MSG_CREAT_NOM        "Nom du loto : "
#define MSG_CREAT_MIN        "Plage de valeur (min) : "
#define MSG_CREAT_MAX        "Plage de valeur (max) : "
#define MSG_CREAT_COMP       "Numeros complementaires ? (o/n) : "
#define MSG_CREAT_MINCOMP    "Plage complementaire (min) : "
#define MSG_CREAT_MAXCOMP    "Plage complementaire (max) : "
#define MSG_CREAT_SIMU       "Mode simulation ? (o/n) : "
#define MSG_CREAT_SIMUNB     "Combien de tirages a generer ? : "
#define MSG_CREAT_PREFIX     "log%s.txt"

// ERREURS
#define ERR_DIR_OPEN         "Impossible d'ouvrir le repertoire courant"
#define ERR_NO_TXT           "Aucun fichier .txt trouve.\n"
#define ERR_INVALID_SELEC    "Selection invalide.\n"
#define ERR_FILE_OPEN        "Erreur !\n"
#define ERR_TABLEAU_PLEIN    "Erreur : tableau plein, impossible d'insérer.\n"
#define ERR_AUCUNE_MODIF     "Erreur : aucune valeur a modifier.\n"
#define ERR_AUCUNE_SUPPR     "Erreur : aucune valeur a supprimer.\n"
#define ERR_SAUVEGARDER      "Erreur : impossible de sauvegarder dans le fichier %s\n"
#define ERR_CHOIX_INV        "Choix invalide.\n"
#define ERR_AUCUNE_DATA      "Aucune donnee.\n"
#define ERR_OUVERTURE        "Erreur lors de l'ouverture ou fichier vide.\n"
#define MSG_SELECT           "Sélectionnez un numéro de fichier (1/%d) : "
#define MSG_SELECTED         "Vous avez sélectionné : %s\n"
#define MSG_VALEUR_INSER     "Valeur insérée\n"
#define MSG_SUPPRIME         "Dernière valeur supprimée.\n"
#define MSG_SAUV_INCO        "Sauvegarde en cours...\n"
#define MSG_FICHIER_MAJ      "Fichier %s mis à jour avec succès.\n"

// AFFICHAGE STATISTIQUES
#define MSG_VAL_PLUS_GAG     "\nValeur la plus gagnante : %d (%d occurrences)\n"
#define MSG_VAL_MOINS_GAG    "\nValeur la moins gagnante : %d (%d occurrences)\n"
#define MSG_6_MEILLEURS      "\n6 meilleurs numeros : "
#define MSG_6_MOINS_BONS     "\n6 moins bons numeros : "
#define MSG_FILE_SORT_VAL    "numéro %d de tirage présent : %d fois\n"
#define MSG_FILE_SORT_TOP    "Les 6 meilleurs numéros à jouer :\n"

// CHAINES
#define EXT_TXT              ".txt"
#define FORMAT_INT           "%d "
#define FORMAT_SCANF_INT     "%d"
#define FORMAT_SCANF_INT_N   "%d\n"
#define FORMAT_SCANF_STR49   "%49s"
#define FORMAT_SCANF_STR39   "%39s"
#define FORMAT_SCANF_CHAR    "%c"
#define FORMAT_SCANF_PTR     "%d"
#define NEWLINE_FICHIER      "\n"
#define REPONSE_OUI_MIN      'o'
#define REPONSE_OUI_MAJ      'O'

#endif /* CONSTANTES_H */
