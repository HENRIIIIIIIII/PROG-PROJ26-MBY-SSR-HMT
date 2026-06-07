//-----------------------------------------------------------------------------------//
// Nom du projet 		: Projet_LOTO
// Nom du fichier 		: main.c
// Date de création 	: 18.05.26
// Date de modification : 07.06.26
//
// Auteurs 				: MBY / SSR / HMT
//
// Version				: 1.0
//
// Description          : 
//
// Remarques :            lien pour la table ASCII :
// 						  -> http://www.asciitable.com/
// 						  lien pour la saisie de clavier avec getc & getchar pour ne pas
//                        avoir des erreurs d'interprétation
// 						  -> http://fr.openclassrooms.com/informatique/cours/utiliser-les-bonnes-fonctions-d-entree
//----------------------------------------------------------------------------------//

#if defined(_MSC_VER)
    // Nécessaire pour compiler sous Windows
    #define _CRT_SECURE_NO_WARNINGS
    #include "dirent.h"
#else
    // Compilation fonctionnelle sous Ubuntu 26.04 LTS
    #ifndef _GNU_SOURCE
        #define _GNU_SOURCE
    #endif
    #include <dirent.h>
#endif

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "constantes.h"
#include "GestionAffichage.h"
#include "GestionValeurlotoGagnante.h"

// Scanne le repertoire courant et retourne le nombre de fichiers .txt
int scannerRepertoireTxt(int file_count, char meme[MAX_FICHIERS][TAILLE_MAX_FICHIER]);

// Affiche la liste des fichiers, lit le choix de l'utilisateur, ouvre le fichier selectionne et lit les valeurs numeriques une par une.
int selectionnerFichier(int move_over, char meme[MAX_FICHIERS][TAILLE_MAX_FICHIER], int file_count, Loto* loto);

// Guide l'utilisateur pour creer un nouveau loto (nom, plages, simulation) puis sauvegarde les donnees dans un fichier txt.
void saisirNouveauLoto(void);

// Vide le buffer d'entree standard apres un scanf pour eviter que les caracteres residuels soient relus.
void viderBuffer(void);

// Ecrit les valeurs du loto dans un fichier texte
void sauvegarderFichierLoto(Loto* loto, const char* nomFichier);

// Affiche le menu principal interactif et execute l'action choisie.
void menuPrincipal(Loto* loto, const char* nomFichierActuel);

int main(void)
{
    // Tableau de stockage des noms de fichiers
    char meme[MAX_FICHIERS][TAILLE_MAX_FICHIER];    

    // Initialisation du générateur de nombres aléatoires avec l'horloge système
    // Permet d'obtenir des séquences différentes à chaque exécution pour la simulation
    srand((unsigned int)time(NULL));

    Loto monLoto = { 0 };
    char nomFichierLotoActuel[TAILLE_MAX_FICHIER] = "";
    char reponse;

    printf(MSG_BIENVENUE);

    // Boucle principale
    while (true)
    {
        int file_count = scannerRepertoireTxt(0, meme);

        if (file_count > 0)
        {
            printf(MSG_LOTO_EXISTANT);
            scanf(FORMAT_SCANF_CHAR, &reponse);
            viderBuffer();
            if (reponse == REPONSE_OUI_MIN || reponse == REPONSE_OUI_MAJ) {
                saisirNouveauLoto();
                printf(MSG_FICHIER_CREE);
                continue;
                // La boucle recommence et trouvera le nouveau fichier
            }

            // L'utilisateur selectionne un fichier a lire
            int move_over = selectionnerFichier(0, meme, file_count, &monLoto);

            if (move_over >= 0)
            {
                // Copie du nom du loto saisi dans le nom du fichier
                strcpy(nomFichierLotoActuel, monLoto.nom);

                printf(MSG_CONFIG_TITLE);
                printf(MSG_CONFIG_INFO, monLoto.nom, monLoto.nbValeurs);

                menuPrincipal(&monLoto, nomFichierLotoActuel);

                // Sortie de la boucle apres avoir quitte le menu
                break;
            }
            else
            {
                printf(ERR_OUVERTURE);
                break;
            }

        }
        else
        {
            // Aucun fichier trouve : on cree un nouveau loto
            saisirNouveauLoto();
            printf(MSG_FICHIER_CREE);
            continue;
            // La boucle recommence et trouvera le nouveau fichier
        }
    }

    return 0;
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
                printf("%s\n", de->d_name);
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
    scanf(FORMAT_SCANF_PTR, &userAnswer);
    viderBuffer();

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
    if (fichier == NULL) {
        // Message d'erreur
        printf(ERR_SAUVEGARDER, nomFichier);
        return;
    }

    // Ecriture des valeurs par blocs de BLOC_SAUVEGARDE pour la lisibilité dans le fichier
    for (int i = 0; i < loto->nbValeurs; i++) {
        fprintf(fichier, FORMAT_INT, loto->valeurs[i]);
        if ((i + 1) % BLOC_SAUVEGARDE == 0) {
            fprintf(fichier, NEWLINE_FICHIER);
        }
    }

    // Si la derniere ligne n'etait pas un multiple de BLOC_SAUVEGARDE, on ajoute un saut
    if (loto->nbValeurs % BLOC_SAUVEGARDE != 0) {
        fprintf(fichier, NEWLINE_FICHIER);
    }

    fclose(fichier);
    printf(MSG_FICHIER_MAJ, nomFichier);
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: viderBuffer
// Description: Vide le buffer d'entree standard apres un scanf pour eviter
//              que les caracteres residuels soient relus.
// Pour en savoir plus : https://intro2c.sdds.ca/D-Modularity/input-functions
//----------------------------------------------------------------------------------//
void viderBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: saisirNouveauLoto
// Description: Guide l'utilisateur pour creer un nouveau loto (nom, plages, simulation)
//              puis sauvegarde les donnees dans un fichier txt.
//----------------------------------------------------------------------------------//
void saisirNouveauLoto(void)
{
    Loto nouveauLoto = { 0 };
    char nomFichier[TAILLE_MAX_FICHIER];
    char reponse;

    printf(MSG_CREAT_TITRE);
    printf(MSG_CREAT_NOM);
    scanf(FORMAT_SCANF_STR49, nouveauLoto.nom);
    viderBuffer();

    printf(MSG_CREAT_MIN);
    scanf(FORMAT_SCANF_INT, &nouveauLoto.minVal);
    viderBuffer();

    printf(MSG_CREAT_MAX);
    scanf(FORMAT_SCANF_INT, &nouveauLoto.maxVal);
    viderBuffer();

    printf(MSG_CREAT_COMP);
    scanf(FORMAT_SCANF_CHAR, &reponse);
    viderBuffer();

    if (reponse == REPONSE_OUI_MIN || reponse == REPONSE_OUI_MAJ) {
        nouveauLoto.nbComplementaires = 1;
        printf(MSG_CREAT_MINCOMP);
        scanf(FORMAT_SCANF_INT, &nouveauLoto.minComp);
        viderBuffer();

        printf(MSG_CREAT_MAXCOMP);
        scanf(FORMAT_SCANF_INT, &nouveauLoto.maxComp);
        viderBuffer();
    }

    printf(MSG_CREAT_SIMU);
    scanf(FORMAT_SCANF_CHAR, &reponse);
    viderBuffer();

    if (reponse == REPONSE_OUI_MIN || reponse == REPONSE_OUI_MAJ) {
        int nbSimul;
        printf(MSG_CREAT_SIMUNB);
        scanf(FORMAT_SCANF_INT, &nbSimul);
        viderBuffer();

        // Generation de valeurs aleatoires dans la plage definie par l'utilisateur
        for (int i = 0; i < nbSimul && i < MAX_VALEURS; i++) {
            nouveauLoto.valeurs[nouveauLoto.nbValeurs++] = nouveauLoto.minVal + rand() % (nouveauLoto.maxVal - nouveauLoto.minVal + 1);
        }
    }

    // Creation du fichier de sauvegarde avec le prefixe "log"
    snprintf(nomFichier, sizeof(nomFichier), MSG_CREAT_PREFIX, nouveauLoto.nom);
    sauvegarderFichierLoto(&nouveauLoto, nomFichier);
}

//----------------------------------------------------------------------------------//
// Nom de la fonction: menuPrincipal
// Entree / Sortie / I/O :  Loto* loto structure du loto en cours
//                          const char* nomFichierActuel nom du fichier courant
// Description: Affiche le menu principal interactif et execute l'action choisie.
//              La boucle se poursuit jusqu'a ce que l'utilisateur choisisse de quitter.
//----------------------------------------------------------------------------------//
void menuPrincipal(Loto* loto, const char* nomFichierActuel)
{
    int choix = 0;
    int valeur;

    do {
        printf(MSG_MENU_TITRE);
        printf(MSG_MENU_1);
        printf(MSG_MENU_2);
        printf(MSG_MENU_3);
        printf(MSG_MENU_4);
        printf(MSG_MENU_5);
        printf(MSG_MENU_6);
        printf(MSG_MENU_7);
        printf(MSG_MENU_8);
        printf(MSG_MENU_9);
        printf(MSG_MENU_CHOIX);

        if (scanf(FORMAT_SCANF_PTR, &choix) != 1) {
            viderBuffer();
            continue;
        }

        switch (choix) {
            case 1:
                printf(MSG_MENU_VALEUR);
                scanf(FORMAT_SCANF_INT, &valeur);
                if (!insererValeur(loto->valeurs, &loto->nbValeurs, valeur)) {
                    printf(ERR_TABLEAU_PLEIN);
                } else {
                    printf(MSG_VALEUR_INSER);
                }
                break;
            case 2:
                printf(MSG_MENU_MODIF);
                scanf(FORMAT_SCANF_INT, &valeur);
                if (!modifierDerniereValeur(loto->valeurs, loto->nbValeurs, valeur)) {
                    printf(ERR_AUCUNE_MODIF);
                }
                break;
            case 3:
                if (!supprimerDerniereValeur(&loto->nbValeurs)) {
                    printf(ERR_AUCUNE_SUPPR);
                } else {
                    printf(MSG_SUPPRIME);
                }
                break;
            case 4:
                if (loto->nbValeurs > 0) {
                    afficherValeurPlusGagnante(loto->valeurs, loto->nbValeurs);
                } else {
                    printf(ERR_AUCUNE_DATA);
                }
                break;
            case 5:
                if (loto->nbValeurs > 0) {
                    afficherValeurMoinsGagnante(loto->valeurs, loto->nbValeurs);
                } else {
                    printf(ERR_AUCUNE_DATA);
                }
                break;
            case 6:
                if (loto->nbValeurs > 0) {
                    afficher6MeilleursNumeros(loto->valeurs, loto->nbValeurs);
                } else {
                    printf(ERR_AUCUNE_DATA);
                }
                break;
            case 7:
                if (loto->nbValeurs > 0) {
                    afficher6MoinsBonsNumeros(loto->valeurs, loto->nbValeurs);
                } else {
                    printf(ERR_AUCUNE_DATA);
                }
                break;
            case 8:
                if (loto->nbValeurs > 0) {
                    trierFichier(loto);
                } else {
                    printf(ERR_AUCUNE_DATA);
                }
                break;
            case 9:
                printf(MSG_SAUV_INCO);
                sauvegarderFichierLoto(loto, nomFichierActuel);
                break;
            default:
                printf(ERR_CHOIX_INV);
        }
    } while (choix != 9);
}
