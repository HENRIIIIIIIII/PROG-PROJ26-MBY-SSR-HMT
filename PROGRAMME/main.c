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
// Directives de compilation
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "constantes.h"
#include "GestionAffichage.h"
#include "GestionValeurlotoGagnante.h"
#include "GestionFichiersLoto.h"
#include "GestionSaisie.h"

// Guide l'utilisateur pour creer un nouveau loto (nom, plages, simulation) puis sauvegarde les donnees dans un fichier txt.
void saisirNouveauLoto(void);

// Affiche le menu principal interactif et execute l'action choisie.
void menuPrincipal(Loto* loto, const char* nomFichierActuel);

int main(void)
{
    // Tableau de stockage des noms de fichiers
    static char meme[MAX_FICHIERS][TAILLE_MAX_FICHIER];    

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
            lireCaractere(&reponse);
            
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

                // Affichage des 6 meilleurs numeros au chargement
                if (monLoto.nbValeurs > 0)
                    afficher6MeilleursNumeros(monLoto.valeurs, monLoto.nbValeurs);

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
    lireChaine(nouveauLoto.nom, TAILLE_MAX_FICHIER);

    printf(MSG_CREAT_MIN);
    lireEntier(&nouveauLoto.minVal);

    printf(MSG_CREAT_MAX);
    lireEntier(&nouveauLoto.maxVal);

    printf(MSG_CREAT_COMP);
    lireCaractere(&reponse);

    if (reponse == REPONSE_OUI_MIN || reponse == REPONSE_OUI_MAJ) {
        nouveauLoto.nbComplementaires = 1;
        printf(MSG_CREAT_MINCOMP);
        lireEntier(&nouveauLoto.minComp);

        printf(MSG_CREAT_MAXCOMP);
        lireEntier(&nouveauLoto.maxComp);
    }

    printf(MSG_CREAT_SIMU);
    lireCaractere(&reponse);

    if (reponse == REPONSE_OUI_MIN || reponse == REPONSE_OUI_MAJ) {
        int nbSimul;
        printf(MSG_CREAT_SIMUNB);
        lireEntier(&nbSimul);

        // Generation de valeurs aleatoires dans la plage definie par l'utilisateur
        for (int i = 0; i < nbSimul && nouveauLoto.nbValeurs < MAX_VALEURS; i++) {
            nouveauLoto.valeurs[nouveauLoto.nbValeurs++] = nouveauLoto.minVal + rand() % (nouveauLoto.maxVal - nouveauLoto.minVal + 1);
        }

        // Generation des numeros complementaires si actives
        if (nouveauLoto.nbComplementaires == 1) {
            for (int i = 0; i < nbSimul && nouveauLoto.nbValeurs < MAX_VALEURS; i++) {
                nouveauLoto.valeurs[nouveauLoto.nbValeurs++] = nouveauLoto.minComp + rand() % (nouveauLoto.maxComp - nouveauLoto.minComp + 1);
            }
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
        printf(MSG_MENU_10);
        printf(MSG_MENU_CHOIX);

        if (scanf(FORMAT_SCANF_INT, &choix) != 1) {
            viderBuffer();
            continue;
        }

        switch (choix) {
            case 1:
                printf(MSG_MENU_VALEUR);
                lireEntier(&valeur);
                if (!insererValeur(loto->valeurs, &loto->nbValeurs, valeur)) {
                    printf(ERR_TABLEAU_PLEIN);
                } else {
                    printf(MSG_VALEUR_INSER);
                }
                break;
            case 2:
                printf(MSG_MENU_MODIF);
                lireEntier(&valeur);
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
                printf(MSG_MENU_TIRAGES, loto->nbValeurs);
                break;
            case 10:
                printf(MSG_SAUV_INCO);
                sauvegarderFichierLoto(loto, nomFichierActuel);
                break;
            default:
                printf(ERR_CHOIX_INV);
        }
    } while (choix != 10);
}
