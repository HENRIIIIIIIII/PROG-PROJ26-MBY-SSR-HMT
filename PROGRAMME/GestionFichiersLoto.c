#if defined(_MSC_VER)
    // Compilation sous Windows
    #include "dirent.h" // Librairie non disponible sous Windows
#else
    // Compilation sous linux
    #ifndef _GNU_SOURCE
        #define _GNU_SOURCE
    #endif
    #include <dirent.h> // Librairie disponible sous Linux
#endif

//-----------------------------------------------------------------------------------//
// Nom du projet 		: GestionFichiersLoto
// Nom du fichier 		: GestionFichiersLoto.c
// Date de création 	: 18.05.26
// Date de modification : 08.06.26
//
// Auteurs 				: MBY / SSR / HMT
//
// Version				: 1.0
//
// Description          :  Le fichier `.c` contient des fonctions de gestion pour ecrit les valeurs du loto dans un fichier texte Scanne.
//                         Affiche la liste des fichiers, lit le choix de l'utilisateur, ouvre le fichier selectionne et lit les valeurs numeriques une par une.
//                          
//                    
// Remarques :            
//----------------------------------------------------------------------------------//


#include "GestionFichiersLoto.h"
#include "GestionSaisie.h"
#include <string.h> // Pour strstr, strcmp, strcpy, strncpy
#include <stdlib.h> // Pour atoi

#include <stdio.h>

//----------------------------------------------------------------------------------//
// Nom de la fonction: sauvegarderFichierLoto
// Entree / Sortie / I/O :  Loto* loto structure contenant les donnees a sauvegarder
//                          const char* nomFichier nom du fichier de sortie
// Description: Ecrit les valeurs du loto dans un fichier texte
//----------------------------------------------------------------------------------//
void sauvegarderFichierLoto(Loto* loto, const char* nomFichier)
{
    // Ouverture du fichier
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) 
    {
        // Message d'erreur
        printf(ERR_SAUVEGARDER, nomFichier);
        return;
    }

    // Ecriture des valeurs par blocs de BLOC_SAUVEGARDE pour la lisibilité dans le fichier
    for (int i = 0; i < loto->nbValeurs; i++) 
    {
		// Ecriture de la valeur actuelle dans le fichier
        fprintf(fichier, FORMAT_INT, loto->valeurs[i]);
        if ((i + 1) % BLOC_SAUVEGARDE == 0) 
        {
			// Ajout d'un saut de ligne apres chaque bloc de valeurs pour une meilleure lisibilite
            fprintf(fichier, NEWLINE_FICHIER);
        }
    }

    // Si la derniere ligne n'etait pas un multiple de BLOC_SAUVEGARDE, on ajoute un saut
    if (loto->nbValeurs % BLOC_SAUVEGARDE != 0) 
    {
        fprintf(fichier, NEWLINE_FICHIER);
    }

    fclose(fichier);
    printf(MSG_FICHIER_MAJ, nomFichier);
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: scannerRepertoireTxt
// Entree / Sortie / I/O :  int file_count compte le nombre de fichiers trouves
//                          char meme[MAX_FICHIERS][TAILLE_MAX_FICHIER] memorise le nom du fichier
// Description: Scanne le repertoire courant et retourne le nombre de fichiers .txt
// Date de modification: 03.06.26
// Remarque: Utilise opendir/readdir/closedir pour parcourir le filesystem
//----------------------------------------------------------------------------------//
int scannerRepertoireTxt(int file_count, char meme[MAX_FICHIERS][TAILLE_MAX_FICHIER])
{
    struct dirent* de;  // Pointeur vers l'entree du repertoire

    // ouverture du repertoire courant
    DIR* dr = opendir(".");

    if (dr == NULL)  // Si impossible d'ouvrir le repertoire
    {
        printf(ERR_DIR_OPEN);
        return 0;
    }

    // Parcours de chaque entree du repertoire
    file_count = 0;
    while ((de = readdir(dr)) != NULL)
    {
        // On ne conserve que les fichiers reguliers (pas les dossiers)
        if (de->d_type == DT_REG)
        {
            // Recherche de l'extension .txt dans le nom du fichier
            char* extension = strstr(de->d_name, EXT_TXT);

            // Verification que l'extension .txt est bien en fin de chaine
            if (extension != NULL && strcmp(extension, EXT_TXT) == 0)
            {
                printf("%i. %s\n", (file_count + 1), de->d_name);
                strcpy(meme[file_count], de->d_name);
                file_count++;
            }
        }
    }
    closedir(dr);
    return file_count;
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: selectionnerFichier
// Entree / Sortie / I/O :  int move_over compteur de decalage (valeur lue par blocs de 3)
//                          char meme[MAX_FICHIERS][TAILLE_MAX_FICHIER] noms des fichiers
//                          int file_count nombre de fichiers disponibles
//                          Loto* loto pointeur vers la structure loto a remplir
// Description: Affiche la liste des fichiers, lit le choix de l'utilisateur,
//              ouvre le fichier selectionne et lit les valeurs numeriques une par une.
// Date de modification: 03.06.26
// Remarque: move_over sert a suivre le nombre de valeurs lues pour la sauvegarde par blocs
//----------------------------------------------------------------------------------//
int selectionnerFichier(int move_over, char meme[MAX_FICHIERS][TAILLE_MAX_FICHIER], int file_count, Loto* loto)
{
    FILE* pointer;
    int userAnswer;  // Numero du fichier selectionne par l'utilisateur

    // Si aucun fichier .txt n'est present dans le repertoire
    if (file_count == 0)
    {
        printf(ERR_NO_TXT);
        return -1;
    }

    // Affichage du menu de selection et lecture du choix utilisateur
    printf(MSG_SELECT, file_count);
    scanf(FORMAT_SCANF_INT, &userAnswer);

    // Validation de l'entree utilisateur (entre 1 et file_count)
    if (userAnswer > 0 && userAnswer <= file_count)
    {
        printf(MSG_SELECTED, meme[userAnswer - 1]);
        strncpy(loto->nom, meme[userAnswer - 1], MAX_NOM_LOTO - 1);
        loto->nom[MAX_NOM_LOTO - 1] = '\0';  // Garantir la terminaison par NULL
    }
    else
    {
        printf(ERR_INVALID_SELEC);
        return -1;
    }

    // Buffer temporaire pour la lecture de chaque valeur texte
    char Text1[TAILLE_BUF_TEXTE];

    // Ouverture du fichier selectionne en lecture
    pointer = fopen(meme[userAnswer - 1], "r");

    // Verification que le fichier s'est bien ouvert
    if (pointer == NULL)
    {
        printf(ERR_FILE_OPEN);
        return -1;
    }

    printf(MSG_VALUES_AFFICHEES);
    loto->nbValeurs = 0;

    // Lecture valeur par valeur depuis le fichier
    // La boucle s'arrete quand on atteint MAX_VALEURS ou la fin du fichier (EOF)
    while (loto->nbValeurs < MAX_VALEURS && fscanf(pointer, FORMAT_SCANF_STR39, Text1) == 1)
    {
        printf(MSG_VALEUR_LUE, Text1);
        // Conversion de la chaine lue en entier et stockage dans le tableau
        loto->valeurs[loto->nbValeurs++] = atoi(Text1);
        // Incrémentation du compteur de decalage (suivi du nombre de valeurs lues)
        move_over += 1;
    }
    printf("\n");

    if (loto->nbValeurs == 0)
    {
        printf(ERR_AUCUNE_DATA);
    }

    fclose(pointer);
    return move_over;
}